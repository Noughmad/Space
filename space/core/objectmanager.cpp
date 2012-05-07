#include "objectmanager.h"
#include "iobjectfactory.h"

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
    mFactories << condition;
}

void ObjectManager::removeFactory(const String& prefix)
{
    FactoryCondition condition = {prefix, 0};
    mFactories.removeAll(condition);
}

