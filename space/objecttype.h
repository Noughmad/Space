#ifndef SPACE_OBJECTTYPE_H
#define SPACE_OBJECTTYPE_H

#include "string.h"

#include <QHash>

class QString;
namespace Space {

struct ObjectType
{
    String identifier;
    String mesh;
    String material;
};

typedef QHash<String, ObjectType> ObjectTypeMap;

}

#endif // SPACE_OBJECTTYPE_H
