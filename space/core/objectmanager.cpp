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
