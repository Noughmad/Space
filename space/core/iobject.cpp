#include "iobject.h"

using namespace Space;

IObject::IObject(const QVariantMap& properties, IObject* parent) : mProperties(properties), mParent(parent)
{

}

IObject::~IObject()
{

}

QVariant IObject::getProperty(const String& name)
{
    return mProperties[QString::fromStdString(name)];
}

void IObject::setProperty(const String& name, const QVariant& value)
{
    mProperties[QString::fromStdString(name)] = value;
}

