#ifndef SPACE_OBJECTTYPE_H
#define SPACE_OBJECTTYPE_H

#include "string.h"

#include <QHash>
#include <QStringList>

class QString;
namespace Space {

class ObjectType
{
public:
    ObjectType();
    ObjectType(const String& identifier);
    ~ObjectType();
    
    void setIdentifier(const String& identifier);
    
    String group() const;
    String type() const;
    String subType() const;
    
    String component(int i) const;
    String identifier() const;
    
private:
    String mIdentifier;
    QStringList mIdList;
};


typedef QHash<String, ObjectType> ObjectTypeMap;

}

#endif // SPACE_OBJECTTYPE_H
