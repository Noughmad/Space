#ifndef SPACE_IOBJECT_H
#define SPACE_IOBJECT_H

#include "core_export.h"
#include "types.h"

#include <OgreVector3.h>
#include <OgreCommon.h>
#include <OgreStringConverter.h>

namespace Ogre
{
    class SceneManager;
    class SceneNode;
    class Vector3;
    class SceneNode;
}

namespace Space {       // tolua_export
    
class IObject {       // tolua_export

public:
    // tolua_begin
    
    enum OrientationPart {
        OrientObject,
        OrientWeapons,
        OrientEngines
    };
    // tolua_end
    
    IObject(const String& identifier, IObject* parent = 0);
    virtual ~IObject();
    
    //tolua_begin
    
    virtual String typeId() const = 0;
    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node) = 0;
    virtual void lookAt(const Ogre::Vector3& position, OrientationPart part);
    
    String getProperty(const String& name) const;
    Real getRealProperty(const String& name) const;
    Ogre::Vector3 getVectorProperty(const String& name) const;
    
    void setProperty(const String& name, const String& value);
    void setProperty(const String& name, double value);
    
    Ogre::Vector3 position() const;
    void setPosition(const Ogre::Vector3& position);
    
    StringSet propertyNames();
    
    
    String id() const;
    void setId(const String& id);
    
    IObject* parent();
    void setParent(IObject* parent);
    
    String identifier() const;
    
    // tolua_end
    
    template <class T> void setProperty(const String& name, const T& value);
    
protected:
    Ogre::SceneNode* mainNode;
    
private:
    String mIdentifier;
    IObject* mParent;
    StringMap map;
    Ogre::NameValuePairList mProperties;
};    // tolua_export

template <class T> void IObject::setProperty(const String& name, const T& value)
{
    setProperty(name, Ogre::StringConverter::toString(value));
}

}       // tolua_export

#endif // SPACE_IOBJECT_H
