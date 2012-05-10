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
