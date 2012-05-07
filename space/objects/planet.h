#ifndef SPACE_PLANET_H
#define SPACE_PLANET_H

#include "core/iobject.h"
#include "core/iobjectfactory.h"


namespace Space {

class Planet : public IObject
{
public:
    Planet(const String& identifier, IObject* parent = 0);
    virtual ~Planet();
    
    virtual String typeId() const;
    virtual void create(Ogre::SceneManager* manager, Ogre::SceneNode* node);
};

SPACE_DECLARE_FACTORY("Celestial/Planet", Planet)

}

#endif // SPACE_PLANET_H
