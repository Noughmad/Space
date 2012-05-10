#include "movementmanager.h"
#include "core/iobject.h"

using namespace Space;

MovementManager::MovementManager()
{

}

MovementManager::~MovementManager()
{

}

void MovementManager::processFrame(Ogre::SceneManager* sceneManager, ObjectNodeMap objects, Real timeSinceLastFrame)
{
    const Real factor = 0.2;
    
    ObjectNodeMap::const_iterator it = objects.cbegin();
    ObjectNodeMap::const_iterator end = objects.cend();
    for (; it != end; ++it)
    {
        Ogre::SceneNode* node = it->second;
        Real revolutionSpeed = it->first->getRealProperty("RevolutionSpeed");
        Real rotationSpeed = it->first->getRealProperty("RotationSpeed");

        node->roll(Ogre::Radian(factor * timeSinceLastFrame * revolutionSpeed));
        try
        {
            Ogre::SceneNode* subNode = dynamic_cast<Ogre::SceneNode*>(node->getChild(it->first->id() + "/RotationNode"));
            subNode->roll(Ogre::Radian(factor * timeSinceLastFrame * rotationSpeed));
        }
        catch (Ogre::ItemIdentityException& e)
        {
            
        }  
    }
}
