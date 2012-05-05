#include "application.h"
#include "object.h"
#include "movementmanager.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OISInputManager.h>

#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <QtCore/QMap>

using namespace Space;

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
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

void Application::setupOgre()
{
    mRoot = new Ogre::Root("plugins.cfg");

    Ogre::ConfigFile cf;
    cf.load("resources.cfg");

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
    
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
    }
    else
    {
        return;
    }
    
    mSceneManager = mRoot->createSceneManager(Ogre::ST_EXTERIOR_REAL_FAR, "SceneManager");
    
    mCamera = mSceneManager->createCamera("PlayerCamera");
    mCamera->setPosition(Ogre::Vector3(0,0,800));
    mCamera->lookAt(Ogre::Vector3(0,0,-3000));
    mCamera->setNearClipDistance(5);
    
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mRoot->addFrameListener(this);
   
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    OIS::InputManager* mInputManager = OIS::InputManager::createInputSystem( pl );
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this); 
    
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
  
    // Create a Light and set its position
    /*
    Ogre::Light* light = mSceneManager->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
    */
    
    mRaySceneQuery = mSceneManager->createRayQuery(Ogre::Ray());
    
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Prepared to Start Rendering ***");
}

void Application::setupGui()
{
    mGuiRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
    
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    
    CEGUI::WindowManager* windowManager = CEGUI::WindowManager::getSingletonPtr();
    CEGUI::Window *sheet = windowManager->createWindow("DefaultWindow", "Space/Sheet");
    
    CEGUI::Window *quit = windowManager->createWindow("TaharezLook/Button", "Space/QuitButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Application::quit, this));
    sheet->addChildWindow(quit);
    
    CEGUI::Window *pause = windowManager->createWindow("TaharezLook/Button", "Space/PauseButton");
    pause->setText("Pause");
    pause->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    pause->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), quit->getHeight()));
    pause->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Application::pause, this));    
    sheet->addChildWindow(pause);
    
    CEGUI::System::getSingleton().setGUISheet(sheet);
    
}

void Application::start()
{
    mPause = false;
    mShutDown = false;
    mRoot->startRendering();
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
    
    CEGUI::System::getSingletonPtr()->injectTimePulse(evt.timeSinceLastEvent);
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
    CEGUI::System::getSingletonPtr()->injectKeyUp(arg.key);
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
    
    CEGUI::System* sys = CEGUI::System::getSingletonPtr();
    sys->injectKeyDown(arg.key);
    sys->injectChar(arg.text);
    
    return true;
}

bool Application::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    CEGUI::System::getSingletonPtr()->injectMouseButtonUp(convertButton(id));
    return true;
}

bool Application::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    if (mSelectedObject)
    {
        mSelectedObject->showBoundingBox(false);
    }
    CEGUI::System::getSingletonPtr()->injectMouseButtonDown(convertButton(id));
        
    CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
    mRaySceneQuery->setRay(mouseRay);
    mRaySceneQuery->setSortByDistance(true);
    
    // Execute query
    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator iter; 
    
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
        mSelectedObject->showBoundingBox(true);
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
    
    CEGUI::System* sys = CEGUI::System::getSingletonPtr();
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
    Ogre::SceneNode* parentNode;
    if (object->parent() && mObjectNodes.contains(object->parent()))
    {
        parentNode = mObjectNodes[object->parent()];
    }
    else
    {
        parentNode = mSceneManager->getRootSceneNode();
    }
    Ogre::SceneNode* node = parentNode->createChildSceneNode();
    mObjectNodes.insert(object, node);
    object->create(mSceneManager, node);
}

void Application::removeObject(Object* object)
{
    Ogre::SceneNode* node = mObjectNodes[object];
    mSceneManager->getRootSceneNode()->removeChild(node);
    delete node;
}

bool Application::quit(const CEGUI::EventArgs& e)
{
    (void)e;
    mShutDown = true;
    return true;
}

bool Application::pause(const CEGUI::EventArgs& e)
{
    mPause = !mPause;
    return true;
}


