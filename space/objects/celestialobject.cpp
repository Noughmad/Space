#include "celestialobject.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreParticleSystem.h>

using namespace Space;

CelestialObject::CelestialObject(const Space::String& type, const Space::String& name, Space::Object* parent) : 
Object(type, name, parent), 
mLight(0),
mLightIntensity(0)
{

}

CelestialObject::~CelestialObject()
{

}

void CelestialObject::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(name() + "/RotationNode", position());
    Real s = mSize / 10.0;
    
    if (mLightIntensity > 0)
    {
        mLight = manager->createLight(name() + "/Light");
        mLight->setType(Ogre::Light::LT_POINT);
        subNode->attachObject(mLight);
    }
    
    String entityName;
    
    if (type() == "Star")
    {
        Ogre::SceneNode* particlesNode = subNode->createChildSceneNode(name() + "/ParticlesNode");
        particlesNode->scale(0.6, 0.6, 0.6);
        s = mSize * 10;
        Ogre::ParticleSystem* particleSystem = manager->createParticleSystem(name() + "/Particles", "Space/Star");
        particleSystem->fastForward(10.0);
        particlesNode->attachObject(particleSystem);
        
        entityName = "Star.mesh";
    }
    else
    {
        entityName = "sphere.mesh";
    }

    subNode->setScale(s,s,s);
    
    Ogre::Entity* entity = manager->createEntity(name(), entityName);
    subNode->attachObject(entity);
}

Real CelestialObject::rotationSpeed() const
{
    return mRotationSpeed;
}

void CelestialObject::setRotationSpeed(Real speed)
{
    mRotationSpeed = speed;
}

Real CelestialObject::revolutionSpeed() const
{
    return mRevolutionSpeed;
}

void CelestialObject::setRevolutionSpeed(Real speed)
{
    mRevolutionSpeed = speed;
}

Real CelestialObject::size() const
{
    return mSize;
}

void CelestialObject::setSize(Real size)
{
    mSize = size;
}

Real CelestialObject::lightIntensity() const
{
    return mLightIntensity;
}

void CelestialObject::setLightIntensity(Real intensity)
{
    mLightIntensity = intensity;
}
