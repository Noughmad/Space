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

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "types.h"

namespace Space {       // tolua_export

class IObject;
class IObjectFactory;

// tolua_begin

struct FactoryCondition
{
    String prefix;
    IObjectFactory* factory;
    
    bool operator==(const FactoryCondition& other);
};

// tolua_end

class ObjectManager {   // tolua_export

private:    
    ObjectManager();
    virtual ~ObjectManager();
    
public:
    // tolua_begin
    static ObjectManager& getSingleton();
    
    void registerFactory(const String& prefix, Space::IObjectFactory* factory);
    void removeFactory(const String& prefix);
    
    IObject* createObject(const String& identifier);
    // tolua_end
    
private:
    List<FactoryCondition>::type mFactories;
};      //tolua_export

}       // tolua_export

#endif // OBJECTMANAGER_H
