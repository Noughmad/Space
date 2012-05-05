#include "celestialobject.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>

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

    Ogre::SceneNode* subNode = node->createChildSceneNode(name() + "RotationNode", position());
    double s = mSize / 10.0;
    subNode->setScale(s,s,s);
    subNode->attachObject(entity);
    
    if (mLightIntensity > 0)
    {
        mLight = manager->createLight(name() + "Light");
        subNode->attachObject(mLight);
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
