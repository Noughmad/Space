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
    Ogre::Entity* entity = manager->createEntity(name(), "sphere.mesh");

    Ogre::SceneNode* subNode = node->createChildSceneNode(name() + "/RotationNode", position());
    Real s = mSize / 10.0;
    subNode->setScale(s,s,s);
    subNode->attachObject(entity);
    
    if (mLightIntensity > 0)
    {
        mLight = manager->createLight(name() + "/Light");
        subNode->attachObject(mLight);
    }
    
    if (type() == "Star")
    {
        Ogre::SceneNode* particlesNode = subNode->createChildSceneNode(name() + "/ParticlesNode");
        Real ps = 50;
        particlesNode->setScale(ps, ps, ps);
        Ogre::ParticleSystem* particleSystem = manager->createParticleSystem(name() + "/Particles", "Space/Star");
        particlesNode->attachObject(particleSystem);
    }
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
