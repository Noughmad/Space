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

SceneNode* Star::create(SceneManager* manager, SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/RotationNode");
    Real size = getReal(OP_Size);
    
    Ogre::Light* light = manager->createLight(id() + "/Light");
    light->setType(Ogre::Light::LT_POINT);
    subNode->attachObject(light);
        
    Ogre::SceneNode* particlesNode = subNode->createChildSceneNode(id() + "/ParticlesNode");
    particlesNode->scale(0.6, 0.6, 0.6);
    Ogre::ParticleSystem* particleSystem = manager->createParticleSystem(id() + "/Particles", "Space/Star");
    particlesNode->attachObject(particleSystem);
    particleSystem->fastForward(10.0);
    
    subNode->setScale(size,size,size);
    
    Ogre::Entity* entity = manager->createEntity(id(), "Star.mesh");
    entity->setMaterialName("Star/" + get(OP_SubType));
    subNode->attachObject(entity);
    return subNode;
}
