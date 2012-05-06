#include "movementmanager.h"
#include "objects/celestialobject.h"

using namespace Space;

MovementManager::MovementManager()
{

}

MovementManager::~MovementManager()
{

}

void MovementManager::processFrame(Ogre::SceneManager* sceneManager, ObjectMap objects, Real timeSinceLastFrame)
{
    const Real factor = 0.1;
    
    ObjectMap::iterator it = objects.begin();
    ObjectMap::iterator end = objects.end();
    for (; it != end; ++it)
    {
        Ogre::SceneNode* node = it.value();
        if (CelestialObject* celestial = dynamic_cast<CelestialObject*>(it.key()))
        {
            node->roll(Ogre::Radian(factor * timeSinceLastFrame * celestial->revolutionSpeed()));
            Ogre::SceneNode* subNode = dynamic_cast<Ogre::SceneNode*>(node->getChild(celestial->name() + "/RotationNode"));
            if (subNode)
            {
                subNode->roll(Ogre::Radian(factor * timeSinceLastFrame * celestial->rotationSpeed()));
            }
        }
    }
}
