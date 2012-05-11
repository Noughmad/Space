#ifndef SPACE_APPLICATION_H
#define SPACE_APPLICATION_H

#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "types.h"

namespace Ogre {
class SceneManager;
class SceneManager;
class SceneNode;
}

namespace CEGUI {
class OgreRenderer;
class EventArgs;
}

namespace Space {       // tolua_export

class IMovementManager;
class IObject;

// tolua_begin

class Application : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{

    // tolua_end
    
public:
    Application();
    virtual ~Application();
    
    void start();       // tolua_export
    
    void setupOgre();
    void setupGui();
    
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual bool windowClosing(Ogre::RenderWindow* rw);
    
    virtual bool keyReleased(const OIS::KeyEvent& arg);
    virtual bool keyPressed(const OIS::KeyEvent& arg);
    
    virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
    virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
    virtual bool mouseMoved(const OIS::MouseEvent& arg);
    
    // tolua_begin
    
    Ogre::SceneManager* sceneManager();
    
    void setMovementManager(IMovementManager* manager);
    
    void addObject(IObject* object);
    void removeObject(IObject* object);
    
    bool pause(const CEGUI::EventArgs& e);
    bool quit(const CEGUI::EventArgs& e);
    
    void updateMap();
    void select(Ogre::SceneNode* node);
    
    void setPositionAnimated(Ogre::SceneNode* node, const Ogre::Vector3& position);
    
    // tolua_end
    
private:
    Ogre::Root* mRoot;
    Ogre::SceneManager* mSceneManager;
    Ogre::Camera* mCamera;
    Ogre::RenderWindow* mWindow;
    
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;
    
    CEGUI::OgreRenderer* mGuiRenderer;

    IMovementManager* mMovementManager;
    
    ObjectNodeMap mObjectNodes;
    NodeObjectMap mNodeObjects;
    ObjectNodeMap mTopNodes;
    
    bool mShutDown;
    bool mPause;
    bool mMousePressedInField;
    
    Ogre::SceneNode* mSelectedObject;
    Ogre::RaySceneQuery* mRaySceneQuery;
    Ogre::SceneNode* mCameraCenterNode;
    Ogre::SceneNode* mCameraPitchNode;
    Ogre::Camera* mMapCamera;
    
    // tolua_begin
};

}

// tolua_end

#endif // SPACE_APPLICATION_H
