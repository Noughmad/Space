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

#include "star.h"
#include "core/iobjectfactory.h"

#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>
#include <OgreEntity.h>

using namespace Space;
using namespace Ogre;

Star::Star(const String& identifier, IObject* parent): IObject(identifier, parent)
{

}

Star::~Star()
{

}

String Star::typeId() const
{
    return "Celestial/Star";
}

SceneNode* Star::create(SceneManager* manager, SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/RotationNode");
    Real size = getReal(OP_Size);
    
    Ogre::Light* light = manager->createLight(id() + "/Light");
    light->setType(Ogre::Light::LT_POINT);
    subNode->attachObject(light);
        
    Ogre::SceneNode* particlesNode = subNode->createChildSceneNode(id() + "/ParticlesNode");
    particlesNode->scale(0.6, 0.6, 0.6);
    Ogre::ParticleSystem* particleSystem = manager->createParticleSystem(id() + "/Particles", "Space/Star");
    particlesNode->attachObject(particleSystem);
    particleSystem->fastForward(10.0);
    
    subNode->setScale(size,size,size);
    
    Ogre::Entity* entity = manager->createEntity(id(), "Star.mesh");
    entity->setMaterialName("Star/" + get(OP_SubType));
    subNode->attachObject(entity);
    return subNode;
}
