/*
 * Copyright 2012 Miha Čančula <miha@noughmad.eu>
 * This file is a part of Space, a library for space simulations
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
/**
 * @brief Represents any visible object in space
 * 
 * This is the main class of the library. 
 * Everything you see on the screen, be it a star, planet, ship, space station, asteroid field, 
 * or any other natural or artificial phenomenon, is an object. 
 * 
 * In order to create any objects, you must subclass the IObject class and implement the create() method. 
 * After that, create a suitable object factory and register it with the ObjectManager. 
 * 
 * Objects are not to be constructed directly, always create them through the ObjectManager. 
 * This way, the library can keep track of all objects.
 * 
 * The Space Core library provides no concrete object classes.
 * However, some objects are included in the Space Objects library. 
 * You can use those or define your own. 
 * 
 * @section Parents
 * 
 * An object may or may not have a parent object. 
 * The parent-child relationship affects moving and rotation, as the relationship is 
 * directly translated into a Ogre::SceneNode hierarchy. Hence moving the parent object
 * always move all its children as well. 
 * 
 * An application using the Space library can also make other use of the object hierarchy. 
 * For example, determining the star a planet is orbiting consists of querying the 
 * planet's parent. 
 * 
 * @section Properties
 * 
 * Space objects have a dynamic property sistem. 
 * Properties are set and accessed by the get() and set() functions. 
 * A property name is always a string, while values can be of any type supported by
 * Ogre::StringConverter::toString(). 
 * 
 * Some predefined property names are included. However, you are free to add your own. 
 * However, note that they are identified by name only, so make sure the names are unique. 
 * 
 **/
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
    
    /**
     * @brief Default constructor
     * 
     * Initializes this objects with a unique @p identifier and a @p parent
     *
     * @param identifier the unique identifier of this object
     * @param parent the parent objects, or 0 if the objects has no parent
     **/
    IObject(const String& identifier, IObject* parent = 0);
    /**
     * @brief Default destructor
     *
     **/
    virtual ~IObject();
    
    //tolua_begin
    
    /**
     * @brief The type of this object
     *
     * Implement this method in a subclass. 
     * It should return the general type of this object, like "Star", "Planet" or "SpaceStation". 
     * More specific identification can be set with the OP_SubType property. 
     * 
     **/
    virtual String typeId() const = 0;
    
    /**
     * @brief Add this object to the scene
     * 
     * Create the whole scene hierarchy belonging to this object and load all the needed data.
     * Everything you construct here must be added to @p node, so that it appears on the scene. 
     * 
     * This method should return the scene node closest to your actual object. 
     * The returned node will be used to determine the position and orientation of the object, 
     * as well as for selection and various position markers. 
     *
     * @param manager the scene manager, used for creating entities and other Ogre objects
     * @param node the top node of this object
     * @return the node used for determining the position and orientation of the object. 
     **/
    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node) = 0;
    
    
    /**
     * @brief Orient the object towards the specified @p position
     * 
     * The @p part specifies which part of the object to rotate. 
     * If the object doesn't have the specified part (no engines or weapons), this function should do nothing. 
     * 
     * The default implementation only orientates the whole object if its main node is specified. 
     *
     * @param position where the object should point
     * @param part which part of the object to rotate
     **/
    virtual void lookAt(const Ogre::Vector3& position, OrientationPart part);
    
    /**
     * Returns the value of this object's property @p name. 
     * 
     * @param name the property name
     * @return the property value, as a string
     **/
    String get(const String& name) const;
    
    /**
     * Returns the value of this object's property @p name, converted to a real number.
     *
     * @param name the property name
     * @return the property value, as a real number
     **/
    Real getReal(const String& name) const;
    
    /**
     * Returns the value of this object's property @p name, converted to a 3D vector.
     *
     * @param name the property name
     * @return the property value, as a 3D vector
     **/
    Ogre::Vector3 getVector(const String& name) const;
    
    /**
     * Set the property @p name to @p value
     *
     * @param name the property name
     * @param value the new property value
     **/
    void set(const String& name, const String& value);
    
    /**
     * Set the property @p name to @p value
     *
     * @param name the property name
     * @param value the new property value
     **/void set(const String& name, double value);
    
     /**
      * Returns the value of this object's OP_Position property
      *
      * @return this object's position in parent coordinates
      **/
     Ogre::Vector3 position() const;
    
    /**
     * Sets this object's OP_Position property to @p position
     * 
     * @param position the new position of this object in parent coordinates
     **/    
    void setPosition(const Ogre::Vector3& position);
    
    /**
     * @brief Set this object's position
     * 
     * This is a convenience method, equivalet to calling
     * 
     * @code
     * setPosition(Ogre::Vector3(x, y, z));
     * @endcode
     **/
    void setPosition(Real x, Real y, Real z);
    
    /**
     * Returns the names of all properties set for this object. 
     * 
     * This includes both the default properties (like OP_Id) and any user-set properties. 
     **/
    StringSet propertyNames();
    
    /**
     * @brief Returns the name of this object
     * 
     * This is not necessarily unique, as there could be objects with the same name but different types.
     * It is meant to be used as a display name. 
     * 
     * To get a unique identifier, use the identifier() function
     * 
     * @sa identifier(), setId()
     * 
     **/
    String id() const;
    
    /**
     * @brief Sets the name of this object
     *
     * @param id the new name of the object
     * @sa id()
     **/
    void setId(const String& id);
    
    /**
     * Returns this object's parent
     **/
    IObject* parent();
    
    /**
     * Sets this object's parent to @p parent
     *
     * @param parent the new parent
     **/
    void setParent(IObject* parent);
    
    /**
     * @brief Returns the unique identifier of this object. 
     * 
     * This is composed of the object's type as returned by IObjectFactor::typeId(), 
     * its subtype as set by the OP_SubType property, and its id(). 
     **/String identifier() const;
    
    // tolua_end
    
    /**
     * @brief The template version of the set() function
     * 
     * The @p value must be of a type supported by Ogre::StringConverter::toString()
     *
     * @param name the property name
     * @param value the new property value
     **/
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
