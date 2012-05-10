#include "asteroidbelt.h"
#include <core/types.h>
#include <OgreSceneNode.h>
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreParticleEmitter.h>

using namespace Space;

AsteroidBelt::AsteroidBelt(const Space::String& identifier, Space::IObject* parent) : IObject(identifier, parent)
{

}

AsteroidBelt::~AsteroidBelt()
{

}

String AsteroidBelt::typeId() const
{
    return "Celestial/Belt";
}

Ogre::SceneNode* AsteroidBelt::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/RotationNode");
    Real size = getProperty<Real>("Size");
    if (size)
    {
        subNode->setScale(size, size, size);
    }
    Ogre::ParticleSystem* system = manager->createParticleSystem(id() + "System", "Space/" + getProperty<String>("SubType"));
    subNode->attachObject(system);
    system->fastForward(100.0);
    
    system->setRenderingDistance(1000.0);
    return subNode;
}
