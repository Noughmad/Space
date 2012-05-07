#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "string.h"

#include <QList>
#include <QPair>

namespace Space 
{

class IObject;
class IObjectFactory;

struct FactoryCondition
{
    String prefix;
    IObjectFactory* factory;
    
    bool operator==(const FactoryCondition& other);
};

class ObjectManager
{

private:    
    ObjectManager();
    virtual ~ObjectManager();
    
public:
    static ObjectManager& getSingleton();
    
    void registerFactory(const String& prefix, IObjectFactory* factory);
    void removeFactory(const String& prefix);
    
    IObject* createObject(const String& identifier);
    
private:
    QList<FactoryCondition> mFactories;
};

}

#endif // OBJECTMANAGER_H
