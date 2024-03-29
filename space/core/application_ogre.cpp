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

#include "application.h"
#include "space_config.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OISInputManager.h>

using namespace Space;
using namespace Ogre;

void Application::setupOgre()
{
    mRoot = new Root(String(DataDir) + "/plugins.cfg");

    ConfigFile cf;
    cf.load(String(DataDir) + "/resources.cfg");

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(
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
    
    mSceneManager = mRoot->createSceneManager(ST_EXTERIOR_REAL_FAR, "SceneManager");
    
    mCameraCenterNode = mSceneManager->getRootSceneNode()->createChildSceneNode("CameraCenter");
    mCameraPitchNode = mCameraCenterNode->createChildSceneNode("CameraPitch");
    
    SceneNode* cameraNode = mCameraPitchNode->createChildSceneNode("CameraNode", Vector3(0,0,2000));
    cameraNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);
    
    mCamera = mSceneManager->createCamera("PlayerCamera");
    mCamera->setDirection(0, 0, -1);
    cameraNode->attachObject(mCamera);
    
    SceneNode* lightNode = cameraNode->createChildSceneNode(Vector3(0, 0, -2000));
    
    Light* light = mSceneManager->createLight("CameraLight");
    light->setType(Light::LT_DIRECTIONAL);
    light->setDirection(0, 0, 1);
    light->setCastShadows(false);
    lightNode->attachObject(light);
    
    mCamera->setNearClipDistance(5);
    mCamera->setFarClipDistance(10000);
    mCamera->setUseRenderingDistance(true);
    
    // Create one viewport, entire window
    Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

    // Set default mipmap level (NB some APIs ignore this)
    TextureManager::getSingleton().setDefaultNumMipmaps(5);

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mRoot->addFrameListener(this);
   
    LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
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
    WindowEventUtilities::addWindowEventListener(mWindow, this); 
    
    mSceneManager->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
  
    mSceneManager->setSkyBox(true, "Space/SpaceSkyBox");
    
    mRaySceneQuery = mSceneManager->createRayQuery(Ray());
    
    LogManager::getSingletonPtr()->logMessage("*** Prepared to Start Rendering ***");
}

void Application::start()
{
    mPause = false;
    mShutDown = false;
    mRoot->startRendering();
}