#include "iobject.h"
#include <OgreSceneNode.h>
#include <OgreStringConverter.h>

using namespace Space;

IObject::IObject(const String& identifier, IObject* parent) : mParent(parent)
{
    set(OP_SubType, identifier.substr(0, identifier.find('/')));
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

String IObject::get(const String& name) const
{
    auto it = mProperties.find(name);
    if (it != mProperties.end())
    {
        return it->second;
    }
    return String();
}

void IObject::set(const String& name, const String& value)
{
    mProperties.insert(std::make_pair(name, value));
}

void IObject::set(const String& name, double value)
{
    set(name, Ogre::StringConverter::toString(Ogre::Real(value)));
}


String IObject::id() const
{
    return get(OP_Id);
}

void IObject::setId(const String& id)
{
    set(OP_Id, id);
}

Ogre::Vector3 IObject::position() const
{
    return getVector("Position");
}

void IObject::setPosition(const Ogre::Vector3& position)
{
    set(OP_Position, position);
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

Real IObject::getReal(const String& name) const
{
    return Ogre::StringConverter::parseReal(get(name));
}

Ogre::Vector3 IObject::getVector(const String& name) const
{
    return Ogre::StringConverter::parseVector3(get(name));
}

void IObject::setPosition(Real x, Real y, Real z)
{
    setPosition(Ogre::Vector3(x,y,z));
}

