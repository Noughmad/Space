#ifndef SPACE_IOBJECTFACTORY_H
#define SPACE_IOBJECTFACTORY_H

#include "core_export.h"
#include "string.h"

namespace Space {

class Object;

class SPACE_CORE_EXPORT IObjectFactory
{

public:
    virtual ~IObjectFactory();
        
    virtual Object* createObject(const String& identifier) = 0;
};

}

#endif // SPACE_IOBJECTFACTORY_H
