#ifndef SPACE_IOBJECTFACTORY_H
#define SPACE_IOBJECTFACTORY_H

#include "core_export.h"
#include "string.h"

namespace Space {

class IObject;

class SPACE_CORE_EXPORT IObjectFactory
{

public:
    virtual ~IObjectFactory();
        
    virtual IObject* createObject(const String& identifier, IObject* parent = 0) = 0;
};

}

#define SPACE_DECLARE_FACTORY(condition, name)                                  \
class name##Factory : public IObjectFactory                                     \
{ public: name##Factory() {} virtual ~name##Factory() {}                        \
virtual IObject* createObject(const String& identifier, IObject* parent = 0)    \
{ return new name(identifier, parent); }  };

#endif // SPACE_IOBJECTFACTORY_H
