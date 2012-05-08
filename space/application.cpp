#include "application.h"
#include "core/iobject.h"
#include "movementmanager.h"
#include "space_config.h"

#include <OgreRenderWindow.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>

#include <CEGUI.h>
#include <CEGUIImageset.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <QtCore/QMap>
#include <QtCore/QString>

using namespace Space;
using namespace CEGUI;

const char* DetailWindowId = "Space/Detail";
const char* DetailContentsId = "Space/Detail/Contents";

MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return LeftButton;
 
    case OIS::MB_Right:
        return RightButton;
 
    case OIS::MB_Middle:
        return MiddleButton;
 
    default:
        return LeftButton;
    }
}

Application::Application() :
mSelectedObject(0),
mShutDown(false),
mMousePressedInField(false)
{
    mMovementManager = new MovementManager();
    
    setupOgre();
    setupGui();
    updateMap();
}

Application::~Application()
{

}

void Application::setupGui()
{
    mGuiRenderer = &OgreRenderer::bootstrapSystem();
    
    Imageset::setDefaultResourceGroup("Imagesets");
    Font::setDefaultResourceGroup("Fonts");
    Scheme::setDefaultResourceGroup("Schemes");
    WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    WindowManager::setDefaultResourceGroup("Layouts");
    
    SchemeManager::getSingleton().create("TaharezLook.scheme");
    System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    
    WindowManager* windowManager = WindowManager::getSingletonPtr();
    Window *sheet = windowManager->loadWindowLayout(Ogre::String(DataDir) + "/space.layout");
    
    Window* quit = windowManager->getWindow("Space/Menu/QuitButton");
    quit->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Application::quit, this));
    
    Window* pause = windowManager->getWindow("Space/Menu/PauseButton");
    pause->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Application::pause, this));   
    
    MultiColumnList* details = dynamic_cast<MultiColumnList*>(windowManager->getWindow(DetailContentsId));
    details->addColumn("Property", 1, UDim(0.4, 0));
    details->addColumn("Value", 2, UDim(0.6, 0));
    
    System::getSingleton().setGUISheet(sheet);    
}

bool Application::frameStarted(const Ogre::FrameEvent& evt)
{
    return true;
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{   
    if(mWindow->isClosed() || mShutDown)
        return false;
    
    if (!mPause)
    {
        mMovementManager->processFrame(mSceneManager, mTopNodes, evt.timeSinceLastEvent);
        CEGUI::WindowManager::getSingletonPtr()->getWindow("Space/Minimap")->invalidateRenderingSurface();
    }
    
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
    
    System::getSingletonPtr()->injectTimePulse(evt.timeSinceLastEvent);
    return true;
}


void Application::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;}

bool Application::windowClosing(Ogre::RenderWindow* rw)
{
    return Ogre::WindowEventListener::windowClosing(rw);
}

bool Application::keyReleased(const OIS::KeyEvent& arg)
{
    System::getSingletonPtr()->injectKeyUp(arg.key);
    return true;
}

bool Application::keyPressed(const OIS::KeyEvent& arg)
{
    switch (arg.key)
    {
        case OIS::KC_ESCAPE:
            mShutDown = true;
            break;
            
        case OIS::KC_RIGHT:
            mCamera->moveRelative(Ogre::Vector3(1.0, 0.0, 0.0));
            break;
            
        case OIS::KC_LEFT:
            mCamera->moveRelative(Ogre::Vector3(-1.0, 0.0, 0.0));
            break;
            
        default:
            break;
    }
    
    System* sys = System::getSingletonPtr();
    sys->injectKeyDown(arg.key);
    sys->injectChar(arg.text);
    
    return true;
}

bool Application::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    mMousePressedInField = false;
    return System::getSingletonPtr()->injectMouseButtonUp(convertButton(id));
}

bool Application::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    if (System::getSingletonPtr()->injectMouseButtonDown(convertButton(id)))
    {
        return true;
    }
    
    if (id == OIS::MB_Left)     // Left mouse button is for selection of objects
    {
        if (mSelectedObject)
        {
            mSelectedObject->showBoundingBox(false);
        }
        
        MultiColumnList* details = dynamic_cast<MultiColumnList*>(WindowManager::getSingletonPtr()->getWindow(DetailContentsId));
        details->resetList();
            
        Point mousePos = MouseCursor::getSingleton().getPosition();
        Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
        mRaySceneQuery->setRay(mouseRay);
        mRaySceneQuery->setSortByDistance(true);
        
        // Execute query
        Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator iter; 
        Ogre::SceneNode* selected = 0;
        for ( iter = result.begin(); iter != result.end(); iter++ )
        {
            if ( iter->movable )
            {
                selected = iter->movable->getParentSceneNode();
                break;
            }
        }
        
        if (selected)
        {
            IObject* object = mObjectNodes.key(selected);
            Ogre::SceneNode* root = mSceneManager->getRootSceneNode();
            
            while (!object && (selected != root) )
            {
                selected = selected->getParentSceneNode();
                object = mObjectNodes.key(selected);
            }
            
            if (object)
            {
                select(selected);
                
                int i = 0;
                foreach (const String& property, object->propertyNames())
                {
                    details->addRow();
                    details->setItem(new ListboxTextItem(property), 1, i);
                    
                    String text;
                    QVariant var = object->getProperty(property);
                    if (var.canConvert<String>())
                    {
                        text = var.value<String>();
                    }
                    else
                    {
                        text = var.toString().toStdString();
                    }
                    details->setItem(new ListboxTextItem(text), 2, i);
                    ++i;
                }
            }
            else
            {
                select(0);
            }
        }
        else
        {
            select(0);
        }
    }
    else if (id = OIS::MB_Right)
    {
        // Right mouse button is for giving orders
        // TODO: Make things to which you could give orders
    }
    
    mMousePressedInField = true;
    return true;
}

bool Application::mouseMoved(const OIS::MouseEvent& arg)
{
    if (mMousePressedInField)
    {
        if (arg.state.buttonDown(OIS::MB_Right))
        {
            Ogre::Real distance = mCamera->getParentNode()->getPosition().z * 0.002;
            mCameraCenterNode->translate(Ogre::Vector3(arg.state.X.rel * distance, -arg.state.Y.rel * distance, 0), Ogre::Node::TS_LOCAL);
        }
        else if (arg.state.buttonDown(OIS::MB_Middle))
        {
            mCameraPitchNode->pitch(Ogre::Radian(arg.state.Y.rel) * 0.005, Ogre::Node::TS_PARENT);
            mCameraCenterNode->roll(Ogre::Radian(arg.state.X.rel) * 0.005, Ogre::Node::TS_PARENT);
        }
        return true;
    }
    
    System* sys = System::getSingletonPtr();
    bool accepted = sys->injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    if (arg.state.Z.rel)
    {
        accepted |= sys->injectMouseWheelChange(arg.state.Z.rel / 120.0f);
    }
    
    if (accepted)
    {
        return true;
    }
    
    if (arg.state.Z.rel)
    {
        Real distance = mCamera->getParentNode()->getPosition().z;
        distance *= (1 - 0.002 * arg.state.Z.rel);
        distance = std::min<Real>(std::max<Real>(distance, 50.0f), 3000.0f);
        mCamera->getParentNode()->setPosition(0, 0, distance);
    }
    
    return true;
}

Ogre::SceneManager* Application::sceneManager()
{
    return mSceneManager;
}

void Application::addObject(IObject* object)
{
    /**
     * There are two nodes for every object. 
     * 
     * The first one ("Master") hold the second one ("Object") and the master nodes of all its children. 
     * It is used for translations and other manipulations of the entire system. 
     * 
     * The object node holds only the object itself and does not affect its children. 
     * It is used for selection, changing size or other manipulations of the object itself. 
     */
    
    Ogre::SceneNode* parentNode;
    if (object->parent() && mObjectNodes.contains(object->parent()))
    {
        parentNode = mTopNodes[object->parent()]->getParentSceneNode();
    }
    else
    {
        parentNode = mSceneManager->getRootSceneNode();
    }
    Ogre::SceneNode* node = parentNode->createChildSceneNode(object->id() + "/Master");
    node = node->createChildSceneNode(object->id() + "/Object");
    mTopNodes.insert(object, node);
    mObjectNodes.insert(object, object->create(mSceneManager, node));
}

void Application::removeObject(IObject* object)
{
    Ogre::SceneNode* node = mObjectNodes[object];
    mSceneManager->getRootSceneNode()->removeChild(node);
    delete node;
}

bool Application::quit(const EventArgs& e)
{
    (void)e;
    mShutDown = true;
    return true;
}

bool Application::pause(const EventArgs& e)
{
    mPause = !mPause;
    return true;
}

void Application::updateMap()
{
    mMapCamera = mSceneManager->createCamera("MinimapCamera");
    mMapCamera->setPosition(0.0, 0.0, 1000.0);
    mMapCamera->lookAt(0.0, 0.0, 0.0);
    
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingletonPtr()->createManual("Minimap",
                                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                                Ogre::TEX_TYPE_2D, 512, 512, 0, 
                                Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
    Ogre::RenderTexture* renderTexture = texture->getBuffer()->getRenderTarget();
    
    renderTexture->addViewport(mMapCamera);
    renderTexture->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
    renderTexture->getViewport(0)->setOverlaysEnabled(false);
    
    CEGUI::Texture& guiTexture = mGuiRenderer->createTexture(texture);
    CEGUI::Imageset& imageset = CEGUI::ImagesetManager::getSingleton().create("MinimapImageset", guiTexture);
    imageset.defineImage("MinimapImage", CEGUI::Point(0, 0), CEGUI::Size(512, 512), CEGUI::Point(0, 0));
    
    CEGUI::Window* window = CEGUI::WindowManager::getSingletonPtr()->getWindow("Space/Minimap");
    window->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageset.getImage("MinimapImage")));
}

void Application::select(Ogre::SceneNode* node)
{
    // First remove any current selections
    Ogre::SceneNode* markerNode;
    try
    {
        markerNode = mSceneManager->getSceneNode("SelectionMarker");
    }
    catch (Ogre::ItemIdentityException& e)
    {
        markerNode = 0;
    }
    
    if (markerNode && markerNode->isInSceneGraph())
    {
        markerNode->getParentSceneNode()->removeChild(markerNode);
        markerNode->setVisible(false);
    }
    
    mSelectedObject = node;
    
    if (!node)
    {
        return;
    }
    
    // If something was selected, attach the marker to its node
    
    if (markerNode)
    {
        node->addChild(markerNode);
        markerNode->setVisible(true);
    }
    else
    {
        markerNode = node->createChildSceneNode("SelectionMarker");
        markerNode->setScale(0.05, 0.05, 0.05);
        Ogre::BillboardSet* set = mSceneManager->createBillboardSet("SelectionMarkerSet", 1);
        set->setMaterialName("SelectionMarker");
        set->createBillboard(0, 0, 0);
        markerNode->attachObject(set);
    }
}


