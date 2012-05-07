#include "iobject.h"

using namespace Space;

IObject::IObject(const String& identifier, IObject* parent) : mIdentifier(identifier), mParent(parent)
{
    setId(identifier.substr(identifier.find_last_of('/')));
}

IObject::~IObject()
{

}

IObject* IObject::parent()
{
    return mParent;
}

void IObject::setParent(IObject* parent)
{
    mParent = parent;
}

QVariant IObject::getProperty(const String& name) const
{
    return mProperties.value(name);
}

void IObject::setProperty(const String& name, const QVariant& value)
{
    mProperties.insert(name, value);
}

String IObject::id() const
{
    return getProperty<String>("Id");
}

void IObject::setId(const String& id)
{
    setProperty("Id", QVariant::fromValue<String>(id));
}

Ogre::Vector3 IObject::position() const
{
    return getProperty<Ogre::Vector3>("Position");
}

void IObject::setPosition(const Ogre::Vector3& position)
{
    setProperty("Position", QVariant::fromValue<Ogre::Vector3>(position));
}

StringList IObject::propertyNames()
{
    return mProperties.keys();
}

