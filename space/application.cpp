#include "application.h"
#include "object.h"
#include "movementmanager.h"
#include "objects/celestialobject.h"
#include "space_config.h"

#include <OgreRenderWindow.h>

#include <CEGUI.h>
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
mSelectedObject(0)
{
    mMovementManager = new MovementManager();
    mShutDown = false;
    
    setupOgre();
    setupGui();
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
    details->addColumn("Property", 1, UDim(0.25, 0));
    details->addColumn("Value", 2, UDim(0.75, 0));
    
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
        mMovementManager->processFrame(mSceneManager, mObjectNodes, evt.timeSinceLastEvent);
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
        mSelectedObject = 0;
        for ( iter = result.begin(); iter != result.end(); iter++ )
        {
            if ( iter->movable )
            {
                mSelectedObject = iter->movable->getParentSceneNode();
                break;
            }
        }
        
        if (mSelectedObject)
        {
            Object* object = mObjectNodes.key(mSelectedObject);
            Ogre::SceneNode* root = mSceneManager->getRootSceneNode();
            
            while (!object && (mSelectedObject != root) )
            {
                mSelectedObject = mSelectedObject->getParentSceneNode();
                object = mObjectNodes.key(mSelectedObject);
            }
            
            Ogre::LogManager::getSingletonPtr()->logMessage("Finished loop to traverse the graph");

            if (object)
            {
                mSelectedObject->showBoundingBox(true);
                
                details->addRow();            
                details->setItem(new ListboxTextItem("Name"), 1, 0);
                details->setItem(new ListboxTextItem(object->name()), 2, 0);
                
                details->addRow();            
                details->setItem(new ListboxTextItem("Type"), 1, 1);
                details->setItem(new ListboxTextItem(object->type()), 2, 1);

                if (CelestialObject* celestial = dynamic_cast<CelestialObject*>(object))
                {
                    details->addRow();            
                    details->setItem(new ListboxTextItem("Size"), 1, 2);
                    details->setItem(new ListboxTextItem(QString::number(celestial->size()).toStdString()), 2, 2);
                }
            }
        }
    }
    else if (id = OIS::MB_Right)
    {
        // Right mouse button is for giving orders
        // TODO: Make things to which you could give orders
    }
    return true;
}

bool Application::mouseMoved(const OIS::MouseEvent& arg)
{
    if (arg.state.buttonDown(OIS::MB_Right))
    {
        mCamera->moveRelative(Ogre::Vector3(arg.state.X.rel, -arg.state.Y.rel, 0));
    }
    else if (int dz = arg.state.Z.rel)
    {
        mCamera->moveRelative(Ogre::Vector3(0, 0, -dz));
    }
    
    System* sys = System::getSingletonPtr();
    sys->injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    if (arg.state.Z.rel)
    {
        sys->injectMouseWheelChange(arg.state.Z.rel / 120.0f);
    }
    
    return true;
}

Ogre::SceneManager* Application::sceneManager()
{
    return mSceneManager;
}

void Application::addObject(Object* object)
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
        parentNode = mObjectNodes[object->parent()]->getParentSceneNode();
    }
    else
    {
        parentNode = mSceneManager->getRootSceneNode();
    }
    Ogre::SceneNode* node = parentNode->createChildSceneNode(object->name() + "/Master");
    node = node->createChildSceneNode(object->name() + "/Object");
    mObjectNodes.insert(object, node);
    
    String id = object->type();
    if (!mObjectTypes.contains(id))
    {
        mObjectTypes[id] = ObjectType(id);
    }
    
    object->create(mSceneManager, node, mObjectTypes[object->type()]);
}

void Application::removeObject(Object* object)
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
