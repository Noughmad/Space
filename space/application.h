#ifndef SPACE_APPLICATION_H
#define SPACE_APPLICATION_H

#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <QMap>
#include "space_types.h"

namespace Ogre {
class SceneManager;
class SceneManager;
}

namespace Space {

class MovementManager;
class Object;

class Application : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{

public:
    Application();
    virtual ~Application();
    
    void start();
    
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual bool windowClosing(Ogre::RenderWindow* rw);
    
    virtual bool keyReleased(const OIS::KeyEvent& arg);
    virtual bool keyPressed(const OIS::KeyEvent& arg);
    
    virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
    virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
    virtual bool mouseMoved(const OIS::MouseEvent& arg);
    
    Ogre::SceneManager* sceneManager();
    
    void addObject(Object* object);
    void removeObject(Object* object);
    
private:
    Ogre::Root* mRoot;
    Ogre::SceneManager* mSceneManager;
    Ogre::Camera* mCamera;
    Ogre::RenderWindow* mWindow;
    
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;
    
    MovementManager* mMovementManager;
    
    ObjectMap mObjectNodes;
    
    bool mShutDown;
};

}

#endif // SPACE_APPLICATION_H
