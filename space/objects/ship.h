#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "core/iobject.h"
#include "core/iobjectfactory.h"


namespace Space {

class Ship : public Space::IObject
{

public:
    Ship(const Space::String& identifier, Space::IObject* parent = 0);
    virtual ~Ship();
    
    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node);
    virtual void lookAt(const Ogre::Vector3& position, OrientationPart part);
    virtual Space::String typeId() const;
};

SPACE_DECLARE_FACTORY("Ship", Ship)

}

#endif // SPACE_SHIP_H
