#include "ship.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>

using namespace Space;

Ship::Ship(const Space::String& identifier, Space::IObject* parent) : IObject(identifier, parent)
{

}

Ship::~Ship()
{

}

Ogre::SceneNode* Ship::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* shipNode = node->createChildSceneNode(id() + "/ShipNode");
    shipNode->roll(Ogre::Degree(-90));
    shipNode->setScale(0.5, 0.5, 0.5);
    
    Ogre::SceneNode* entityNode = shipNode->createChildSceneNode(id() + "/EntityNode");
    entityNode->setScale(0.4, 0.4, 0.4);
    Ogre::Entity* entity = manager->createEntity(id(), "Probe.mesh");
    entityNode->attachObject(entity);
    
    mainNode = node;
    return shipNode;
}

Space::String Ship::typeId() const
{
    return "Ship";
}

void Ship::lookAt(const Ogre::Vector3& position, IObject::OrientationPart part)
{
    switch (part)
    {
        case OrientObject:
            mainNode->lookAt(position, Ogre::Node::TS_WORLD);
            break;
            
        case OrientWeapons:
            Ogre::LogManager::getSingletonPtr()->logMessage("Orienting weapons, not yet supported");
            break;
    }
}
