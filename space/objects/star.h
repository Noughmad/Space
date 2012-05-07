#ifndef SPACE_STAR_H
#define SPACE_STAR_H

#include "core/iobject.h"
#include "core/iobjectfactory.h"

namespace Space {

class Star : public IObject
{

public:
    Star(const String& identifier, IObject* parent = 0);
    virtual ~Star();
    
    virtual String typeId() const;
    
    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node);
};

SPACE_DECLARE_FACTORY("Celestial/Star", Star)


}

#endif // SPACE_STAR_H
