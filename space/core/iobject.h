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

// tolua_begin
namespace Space 
{
    // tolua_end
    
    const String OP_Id = "Id";
    const String OP_SubType = "SubType";
    const String OP_Position = "Position";
    
    const String OP_Size = "Size";
    const String OP_RotationSpeed = "RotationSpeed";
    const String OP_RevolutionSpeed = "RevolutionSpeed";
    
    // tolua_begin
class IObject
{
// tolua_end

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
    
    String get(const String& name) const;
    Real getReal(const String& name) const;
    Ogre::Vector3 getVector(const String& name) const;
    
    void set(const String& name, const String& value);
    void set(const String& name, double value);
    
    Ogre::Vector3 position() const;
    void setPosition(const Ogre::Vector3& position);
    void setPosition(Real x, Real y, Real z);
    
    StringSet propertyNames();
    
    
    String id() const;
    void setId(const String& id);
    
    IObject* parent();
    void setParent(IObject* parent);
    
    String identifier() const;
    
    // tolua_end
    
    template <class T> void set(const String& name, const T& value);
    
protected:
    Ogre::SceneNode* mainNode;
    
private:
    String mIdentifier;
    IObject* mParent;
    StringMap map;
    Ogre::NameValuePairList mProperties;
};    // tolua_export

template <class T> void IObject::set(const String& name, const T& value)
{
    set(name, Ogre::StringConverter::toString(value));
}

}       // tolua_export

#endif // SPACE_IOBJECT_H
