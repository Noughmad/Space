#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include "core_export.h"
#include "string.h"

#include <QVariant>

namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

namespace Space {
    
class SPACE_CORE_EXPORT IObject
{

public:
    IObject(const QVariantMap& properties = QVariantMap(), IObject* parent = 0);
    virtual ~IObject();
    
    virtual String typeId() const = 0;
    virtual String id() const = 0;

    virtual void create(Ogre::SceneManager* manager, Ogre::SceneNode* node) = 0;
    
    void setProperty(const String& name, const QVariant& value);
    QVariant getProperty(const String& name);
    template <class T> T getProperty(const String& name);
    
private:
    QVariantMap mProperties;
    IObject* mParent;
};

template <class T> T IObject::getProperty(const String& name)
{
    return getProperty(name).value<T>();
}


}

#endif // SPACE_OBJECT_H
