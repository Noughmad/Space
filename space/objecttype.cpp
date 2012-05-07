#include "objecttype.h"

using namespace Space;

ObjectType::ObjectType()
{
    setIdentifier("Invalid");
}

ObjectType::ObjectType(const String& identifier)
{
    setIdentifier(identifier);
}

void ObjectType::setIdentifier(const String& identifier)
{
    mIdentifier = identifier;
    mIdList = split(identifier);
    while (mIdList.size() < 3)
    {
        mIdList << "None";
    }
}


ObjectType::~ObjectType()
{

}

String ObjectType::group() const
{
    return component(0);
}

String ObjectType::type() const
{
    return component(1);
}

String ObjectType::subType() const
{
    return component(2);
}

String ObjectType::component(int i) const
{
    return mIdList.at(i);
}

String ObjectType::identifier() const
{
    return mIdentifier;
}
