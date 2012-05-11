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

#include "ship.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>

using namespace Space;

Ship::Ship(const Space::String& identifier, Space::IObject* parent) : IObject(identifier, parent)
{

}

Ship::~Ship()
{

}

Ogre::SceneNode* Ship::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* shipNode = node->createChildSceneNode(id() + "/ShipNode");
    shipNode->roll(Ogre::Degree(-90));
    shipNode->setScale(0.5, 0.5, 0.5);
    
    Ogre::SceneNode* entityNode = shipNode->createChildSceneNode(id() + "/EntityNode");
    entityNode->setScale(0.4, 0.4, 0.4);
    Ogre::Entity* entity = manager->createEntity(id(), "Probe.mesh");
    entityNode->attachObject(entity);
    
    mainNode = node;
    return shipNode;
}

Space::String Ship::typeId() const
{
    return "Ship";
}

void Ship::lookAt(const Ogre::Vector3& position, IObject::OrientationPart part)
{
    switch (part)
    {
        case OrientObject:
            mainNode->lookAt(position, Ogre::Node::TS_WORLD);
            break;
            
        case OrientWeapons:
            Ogre::LogManager::getSingletonPtr()->logMessage("Orienting weapons, not yet supported");
            break;
    }
}
