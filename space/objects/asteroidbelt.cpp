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

#include "asteroidbelt.h"
#include <core/types.h>
#include <OgreSceneNode.h>
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreParticleEmitter.h>

using namespace Space;

AsteroidBelt::AsteroidBelt(const Space::String& identifier, Space::IObject* parent) : IObject(identifier, parent)
{

}

AsteroidBelt::~AsteroidBelt()
{

}

String AsteroidBelt::typeId() const
{
    return "Celestial/Belt";
}

Ogre::SceneNode* AsteroidBelt::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/RotationNode");
    Real size = getReal("Size");
    if (size)
    {
        subNode->setScale(size, size, size);
    }
    Ogre::ParticleSystem* system = manager->createParticleSystem(id() + "System", "Space/" + get("SubType"));
    subNode->attachObject(system);
    system->fastForward(100.0);
    
    system->setRenderingDistance(1000.0);
    return subNode;
}
