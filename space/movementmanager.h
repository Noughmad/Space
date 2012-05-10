#ifndef SPACE_MOVEMENTMANAGER_H
#define SPACE_MOVEMENTMANAGER_H

#include <OgreSceneManager.h>
#include "core/types.h"

namespace Space {

class MovementManager
{

public:
    MovementManager();
    virtual ~MovementManager();
    
    virtual void processFrame(Ogre::SceneManager* sceneManager, ObjectNodeMap objects, Real timeSinceLastFrame);
};

}

#endif // SPACE_MOVEMENTMANAGER_H
