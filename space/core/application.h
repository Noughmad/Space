/*
 * Copyright 2012 Miha Čančula <miha@noughmad.eu>
 * This file is a part of Space, a library for space simulations
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

/**
 * @brief A base application class for the Space library
 * 
 * This class encapsulates various aspects of the rendering system, user input and user interface. 
 * 
 * The behavior of input events can be overriden by subclassing and reimplementing the appropriate event handlers. 
 **/
class Application : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{

    // tolua_end
    
public:
    /**
     * @brief Creates the application
     * 
     * Note the the constructor already initializes the entire system, so the contructed application is in a valid state. 
     * You can change the scene by accessing the sceneManager() method, or add objects using addObject().  
     *
     **/
    Application();
    virtual ~Application();
    
    /**
     * Starts the main rendering loop
     *
     **/
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
    
    /**
     * @brief Returns the scene manager
     * 
     **/
    Ogre::SceneManager* sceneManager();
    
    void setMovementManager(IMovementManager* manager);
    
    /**
     * @brief Adds an object to the scene
     *
     * @param object the new object to add
     **/
    void addObject(IObject* object);
    /**
     * @brief Removes the object from the scene
     *
     * @param object the object to remove
     **/
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
