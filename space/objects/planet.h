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

#ifndef SPACE_PLANET_H
#define SPACE_PLANET_H

#include "core/iobject.h"
#include "core/iobjectfactory.h"


namespace Space {

class Planet : public IObject
{
public:
    Planet(const String& identifier, IObject* parent = 0);
    virtual ~Planet();
    
    virtual String typeId() const;
    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node);
};

SPACE_DECLARE_FACTORY("Celestial/Planet", Planet)

}

#endif // SPACE_PLANET_H
