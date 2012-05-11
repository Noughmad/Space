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

#ifndef SPACE_IOBJECTFACTORY_H
#define SPACE_IOBJECTFACTORY_H

#include "core_export.h"
#include "types.h"

namespace Space { // tolua_export

class IObject;

/**
 * @brief A factory for creating IObject instances
 * 
 * The ObjectManager uses factories for the actual creating of objects. 
 * @sa ObjectManager::registerFactory(), ObjectManager::createObject()
 **/
class IObjectFactory {  // tolua_export

public:
    /**
     * @brief Default destructor
     *
     **/
    virtual ~IObjectFactory();
        
    // tolua_begin
    /**
     * @brief Create an object, identified by @p identifier with parent @p parent
     * 
     * The main factory method for creating game objects. 
     * The @p identifier should contain all the information necessary for creating the object. 
     * Its properties can be set later. 
     * 
     * If the factory determines the supplied @p identifier is not supported, return 0. 
     * 
     * @param identifier the unique identifier of the object
     * @param parent the object's parent
     * @return The newly created object
     **/
    virtual IObject* createObject(const String& identifier, IObject* parent = 0) = 0;
};      

}

// tolua_end

#define SPACE_DECLARE_FACTORY(condition, name)                                  \
class name##Factory : public IObjectFactory                                     \
{ public: name##Factory() {} virtual ~name##Factory() {}                        \
virtual IObject* createObject(const String& identifier, IObject* parent = 0)    \
{ return new name(identifier, parent); }  };

#endif // SPACE_IOBJECTFACTORY_H
