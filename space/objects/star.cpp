#include "star.h"
#include "core/iobjectfactory.h"

#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>
#include <OgreEntity.h>

using namespace Space;
using namespace Ogre;

Star::Star(const String& identifier, IObject* parent): IObject(identifier, parent)
{

}

Star::~Star()
{

}

String Star::typeId() const
{
    return "Celestial/Star";
}

void Star::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/RotationNode", position());
    Real size = getProperty<Real>("Size");
    
    Ogre::Light* light = manager->createLight(id() + "/Light");
    light->setType(Ogre::Light::LT_POINT);
    subNode->attachObject(light);
        
    Ogre::SceneNode* particlesNode = subNode->createChildSceneNode(id() + "/ParticlesNode");
    particlesNode->scale(0.6, 0.6, 0.6);
    Ogre::ParticleSystem* particleSystem = manager->createParticleSystem(id() + "/Particles", "Space/Star");
    particleSystem->fastForward(10.0);
    particlesNode->attachObject(particleSystem);
    
    subNode->setScale(size,size,size);
    
    Ogre::Entity* entity = manager->createEntity(id(), "Star.mesh");
    if (!Ogre::MaterialManager::getSingletonPtr()->getByName(getProperty<String>("SubType")).isNull())
    {
        entity->setMaterialName(getProperty<String>("SubType"));
    }
    subNode->attachObject(entity);
}
