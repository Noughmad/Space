#ifndef SPACE_ASTEROIDBELT_H
#define SPACE_ASTEROIDBELT_H

#include "core/iobject.h"
#include "core/iobjectfactory.h"


namespace Space {

class AsteroidBelt : public Space::IObject
{

public:
    AsteroidBelt(const String& identifier, IObject* parent = 0);
    virtual ~AsteroidBelt();
    
    virtual String typeId() const;
    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node);
};

SPACE_DECLARE_FACTORY("Celestial/Belt", AsteroidBelt)

}

#endif // SPACE_ASTEROIDBELT_H
