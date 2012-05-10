#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include "core_export.h"
#include "string.h"
#include "types.h"

#include <QVariant>
#include <QMap>
#include <OgreVector3.h>

namespace Ogre
{
    class SceneManager;
    class SceneNode;
    class Vector3;
class SceneNode;
}

namespace Space {       // tolua_export
    
class SPACE_CORE_EXPORT IObject {       // tolua_export

public:
    // tolua_begin
    
    enum OrientationPart {
        OrientObject,
        OrientWeapons,
        OrientEngines
    };
    
    
    IObject(const String& identifier, IObject* parent = 0);
    virtual ~IObject();
    
    
    virtual String typeId() const = 0;
    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node) = 0;
    virtual void lookAt(const Ogre::Vector3& position, OrientationPart part);
    
    QVariant getProperty(const String& name) const;
    void setProperty(const String& name, const QVariant& value);
    
    // tolua_end
    
    template <class T> T getProperty(const String& name) const;
    template <class T> void setProperty(const String& name, const T& value);
    
    Ogre::Vector3 position() const;
    void setPosition(const Ogre::Vector3& position);
    
    StringList propertyNames();
    
    // tolua_begin
    
    String id() const;
    void setId(const String& id);
    
    IObject* parent();
    void setParent(IObject* parent);
    
    String identifier() const;
    
    // tolua_end
    
protected:
    Ogre::SceneNode* mainNode;
    
private:
    String mIdentifier;
    IObject* mParent;
    QMap<String, QVariant> mProperties;
};    // tolua_export

template <class T> T IObject::getProperty(const String& name) const
{
    return getProperty(name).value<T>();
}

template <class T> void IObject::setProperty(const String& name, const T& value)
{
    return setProperty(name, QVariant::fromValue<T>(value));
}

}       // tolua_export

Q_DECLARE_METATYPE(Ogre::Vector3)

#endif // SPACE_OBJECT_H
