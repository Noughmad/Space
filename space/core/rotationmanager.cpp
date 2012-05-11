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

#include "rotationmanager.h"
#include "iobject.h"

#include <OgreMath.h>
#include <OgreException.h>
#include <OgreSceneNode.h>

using namespace Space;

RotationManager::RotationManager(Real timeFactor) : mTimeFactor(timeFactor)
{

}

RotationManager::~RotationManager()
{

}

void RotationManager::processFrame(Ogre::SceneManager* sceneManager, ObjectNodeMap objects, Real timeSinceLastFrame)
{
    ObjectNodeMap::const_iterator it = objects.cbegin();
    ObjectNodeMap::const_iterator end = objects.cend();
    for (; it != end; ++it)
    {
        Ogre::SceneNode* node = it->second;
        Real revolutionSpeed = it->first->getReal(OP_RevolutionSpeed);
        Real rotationSpeed = it->first->getReal(OP_RotationSpeed);

        node->roll(Ogre::Radian(mTimeFactor * timeSinceLastFrame * revolutionSpeed));
        try
        {
            Ogre::SceneNode* subNode = dynamic_cast<Ogre::SceneNode*>(node->getChild(it->first->id() + "/RotationNode"));
            subNode->roll(Ogre::Radian(mTimeFactor * timeSinceLastFrame * rotationSpeed));
        }
        catch (Ogre::ItemIdentityException& e)
        {
            
        }  
    }
}

