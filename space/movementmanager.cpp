#include "movementmanager.h"
#include "core/iobject.h"

using namespace Space;

MovementManager::MovementManager()
{

}

MovementManager::~MovementManager()
{

}

void MovementManager::processFrame(Ogre::SceneManager* sceneManager, ObjectMap objects, Real timeSinceLastFrame)
{
    const Real factor = 0.2;
    
    ObjectMap::iterator it = objects.begin();
    ObjectMap::iterator end = objects.end();
    for (; it != end; ++it)
    {
        Ogre::SceneNode* node = it.value();
        Real revolutionSpeed = it.key()->getProperty<Real>("RevolutionSpeed");
        Real rotationSpeed = it.key()->getProperty<Real>("RotationSpeed");

        node->roll(Ogre::Radian(factor * timeSinceLastFrame * revolutionSpeed));
        Ogre::SceneNode* subNode = dynamic_cast<Ogre::SceneNode*>(node->getChild(it.key()->id() + "/RotationNode"));
        if (subNode)
        {
            subNode->roll(Ogre::Radian(factor * timeSinceLastFrame * rotationSpeed));
        }
    }
}
