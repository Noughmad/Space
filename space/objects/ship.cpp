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
    Ogre::SceneNode* shipNode = node->createChildSceneNode(id() + "/ShipNode", position());
    shipNode->roll(Ogre::Degree(-90));
    shipNode->setScale(0.5, 0.5, 0.5);
    
    Ogre::SceneNode* entityNode = shipNode->createChildSceneNode(id() + "/EntityNode");
    entityNode->setScale(0.4, 0.4, 0.4);
    Ogre::Entity* entity = manager->createEntity(id(), "Probe.mesh");
    entityNode->attachObject(entity);
    
    return shipNode;
}

Space::String Ship::typeId() const
{
    return "Ship";
}
