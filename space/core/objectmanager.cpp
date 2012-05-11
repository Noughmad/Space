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

#include "objectmanager.h"
#include "iobjectfactory.h"

#include <iostream>

using namespace Space;

bool FactoryCondition::operator==(const FactoryCondition& other)
{
    return (this->prefix == other.prefix);
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

ObjectManager& ObjectManager::getSingleton()
{
    static ObjectManager instance;
    return instance;
}

void ObjectManager::registerFactory(const String& prefix, IObjectFactory* factory)
{
    FactoryCondition condition = {prefix, factory};
    mFactories.push_back(condition);
}

void ObjectManager::removeFactory(const String& prefix)
{
    FactoryCondition condition = {prefix, 0};
    mFactories.remove(condition);
}

IObject* ObjectManager::createObject(const String& identifier)
{
    std::cout << "Trying to create object " << identifier << std::endl;
    foreach (const FactoryCondition& condition, mFactories)
    {
        int p = condition.prefix.size();
        if (condition.prefix.compare(identifier.substr(0, p)) == 0)
        {
            if (IObject* ret = condition.factory->createObject(identifier.substr(p+1)))
            {
                std::cout << "Created object " << identifier.substr(p+1) << " with factory " << condition.prefix << std::endl;
                return ret;
            }
        }
    }
    
    return 0;
}
