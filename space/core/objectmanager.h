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
