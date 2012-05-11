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

class IObjectFactory {  // tolua_export

public:
    virtual ~IObjectFactory();
        
    // tolua_begin
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
