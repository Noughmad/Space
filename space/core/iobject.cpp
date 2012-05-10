#include "iobject.h"
#include <OgreSceneNode.h>
#include <OgreStringConverter.h>

using namespace Space;

IObject::IObject(const String& identifier, IObject* parent) : mParent(parent)
{
    setProperty("SubType", identifier.substr(0, identifier.find('/')));
    setId(identifier.substr(identifier.find_last_of('/')));
    mIdentifier = identifier;
    mainNode = 0;
}

IObject::~IObject()
{

}

void IObject::lookAt(const Ogre::Vector3& position, IObject::OrientationPart part)
{
    if (mainNode && part == OrientObject)
    {
        mainNode->lookAt(position, Ogre::Node::TS_WORLD);
    }
}

IObject* IObject::parent()
{
    return mParent;
}

void IObject::setParent(IObject* parent)
{
    mParent = parent;
}

String IObject::getProperty(const String& name) const
{
    auto it = mProperties.find(name);
    if (it != mProperties.end())
    {
        return it->second;
    }
    return String();
}

void IObject::setProperty(const String& name, const String& value)
{
    mProperties.insert(std::make_pair(name, value));
}

void IObject::setProperty(const String& name, double value)
{
    setProperty(name, Ogre::StringConverter::toString(Ogre::Real(value)));
}


String IObject::id() const
{
    return getProperty("Id");
}

void IObject::setId(const String& id)
{
    setProperty("Id", id);
}

Ogre::Vector3 IObject::position() const
{
    return getVectorProperty("Position");
}

void IObject::setPosition(const Ogre::Vector3& position)
{
    setProperty("Position", position);
}

StringSet IObject::propertyNames()
{
    StringSet set;
    for (Ogre::NameValuePairList::const_iterator it = mProperties.cbegin(); it != mProperties.cend(); ++it)
    {
        set.insert(it->first);
    }
    return set;
}

String IObject::identifier() const
{
    return typeId() + '/' + mIdentifier;
}

Real IObject::getRealProperty(const String& name) const
{
    return Ogre::StringConverter::parseReal(getProperty(name));
}

Ogre::Vector3 IObject::getVectorProperty(const String& name) const
{
    return Ogre::StringConverter::parseVector3(getProperty(name));
}

void IObject::setPosition(Real x, Real y, Real z)
{
    setPosition(Ogre::Vector3(x,y,z));
}

