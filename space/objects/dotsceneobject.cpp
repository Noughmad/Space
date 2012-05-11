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

#include "dotsceneobject.h"
#include "dotsceneloader.h"
#include <OgreSceneNode.h>

using namespace Space;

DotSceneObject::DotSceneObject(const Space::String& identifier, Space::IObject* parent) : IObject(identifier, parent)
{

}

DotSceneObject::~DotSceneObject()
{

}

Ogre::SceneNode* DotSceneObject::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/Node");
    
    String sceneFile;
    if (propertyNames().count("SceneFileName"))
    {
        sceneFile = get("SceneFileName");
    }
    else
    {
        sceneFile = get(OP_SubType) + ".scene";
        Ogre::StringUtil::toLowerCase(sceneFile);
    }
    
    DotSceneLoader loader;
    loader.parseDotScene(sceneFile, "Objects", manager, subNode, id() + "/");
    
    return subNode;
}

Space::String DotSceneObject::typeId() const
{
    return "Data";
}
