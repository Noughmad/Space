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

#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include "space_export.h"
#include "space_types.h"

namespace Ogre
{
    class SceneNode;
    class SceneManager;
}

namespace Space {

class SPACE_EXPORT Object
{
    
public:
    Object(const Space::String& type, const Space::String& name, Space::Object* parent = 0);
    virtual ~Object();
    
    String type() const;
    void setType(const String& type);
    
    String name() const;
    void setName(const String& name);

    Coordinates position() const;
    void setPosition(const Coordinates& position);
    
    Object* parent() const;
    void setParent(Object* parent);
        
    virtual void create(Ogre::SceneManager* manager, Ogre::SceneNode* node);
    
private:
    String mType;
    String mName;
    Coordinates mPosition;
    Object* mParent;    
};

}

#endif // SPACE_OBJECT_H
