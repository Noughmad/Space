#ifndef SPACE_MOVEMENTMANAGER_H
#define SPACE_MOVEMENTMANAGER_H

#include <OgreSceneManager.h>
#include "space_types.h"

namespace Space {

class MovementManager
{

public:
    MovementManager();
    virtual ~MovementManager();
    
    virtual void processFrame(Ogre::SceneManager* sceneManager, ObjectMap objects, Real timeSinceLastFrame);
};

}

#endif // SPACE_MOVEMENTMANAGER_H
