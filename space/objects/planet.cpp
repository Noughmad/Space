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

#include "planet.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include "core/types.h"

using namespace Space;

SPACE_DECLARE_FACTORY("/Celestial/Planet", Planet);

Planet::Planet(const String& identifier, IObject* parent): IObject(identifier, parent)
{
    
}

Planet::~Planet()
{

}

String Planet::typeId() const
{
    return "Celestial/Planet/";
}

Ogre::SceneNode* Planet::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/RotationNode");
    
    Real size = getReal(OP_Size);
    
    subNode = subNode->createChildSceneNode(id() + "/BaseNode");
    subNode->pitch(Ogre::Degree(90));
    
    subNode->setScale(size,size,size);
    
    Ogre::Entity* entity = manager->createEntity(id(), "Planet.mesh");
    entity->setMaterialName("Planet/" + get(OP_SubType));
    subNode->attachObject(entity);
    return subNode;
}

