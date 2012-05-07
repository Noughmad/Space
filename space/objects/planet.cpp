#include "planet.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include "core/types.h"

using namespace Space;

SPACE_DECLARE_FACTORY("/Celestial/Planet", Planet);

Planet::Planet(const String& identifier, IObject* parent): IObject(identifier, parent)
{
    
}

Planet::~Planet()
{

}

String Planet::typeId() const
{
    return "Celestial/Planet/" + getProperty<String>("SubType");
}

Ogre::SceneNode* Planet::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/RotationNode", position());
    Real size = getProperty<Real>("Size");
    
    subNode = subNode->createChildSceneNode(id() + "/BaseNode");
    subNode->pitch(Ogre::Degree(90));
    
    subNode->setScale(size,size,size);
    
    Ogre::Entity* entity = manager->createEntity(id(), "Planet.mesh");
    String subType = getProperty<String>("SubType");
    if (!Ogre::MaterialManager::getSingletonPtr()->getByName(subType).isNull())
    {
        entity->setMaterialName(subType);
    }
    subNode->attachObject(entity);
    return subNode;
}

