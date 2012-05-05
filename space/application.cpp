#include "application.h"
#include "object.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OISInputManager.h>

#include <QtCore/QMap>

using namespace Space;


Application::Application()
{
    
    mShutDown = false;
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
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
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
    Ogre::Light* light = mSceneManager->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
    
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Prepared to Start Rendering ***");
}

Application::~Application()
{

}

void Application::start()
{
    mRoot->startRendering();
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{   
    if(mWindow->isClosed() || mShutDown)
        return false;
    
    foreach (Ogre::SceneNode* node, mObjectNodes)
    {
      //  node->roll(Ogre::Radian(evt.timeSinceLastEvent));
    }
    
    mSceneManager->getRootSceneNode()->roll(Ogre::Radian(evt.timeSinceLastEvent));

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
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
    return true;
}

bool Application::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    return true;
}

bool Application::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
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
    Ogre::SceneNode* node = parentNode->createChildSceneNode(object->position());
    mObjectNodes.insert(object, node);
    object->create(mSceneManager, node);
}
