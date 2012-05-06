/*  This file is part of Space, the free space simulation library
    Copyright 2012 Miha Čančula <miha@noughmad.eu>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "object.h"
#include "objecttype.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

using namespace Space;

Object::Object(const String& type, const String& name, Object* parent) :
mType(type),
mName(name),
mParent(parent)
{
    
}

Object::~Object()
{
    
}

String Object::name() const
{
    return mName;
}

void Object::setName(const String& name)
{
    mName = name;
}

String Object::type() const
{
    return mType;
}

void Object::setType(const String& type)
{
    mType = type;
}

Coordinates Object::position() const
{
    return mPosition;
}

void Object::setPosition(const Coordinates& position)
{
    mPosition = position;
}

Object* Object::parent() const
{
    return mParent;
}

void Object::setParent(Object* parent)
{
    mParent = parent;
}

void Object::create(Ogre::SceneManager* manager, Ogre::SceneNode* node, const ObjectType& type)
{
    
}





