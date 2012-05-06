#ifndef SPACE_CELESTIALOBJECT_H
#define SPACE_CELESTIALOBJECT_H

#include "../object.h"

namespace Ogre {
class Light;
}


namespace Space {

class CelestialObject : public Space::Object
{

public:
    CelestialObject(const Space::String& type, const Space::String& name, Space::Object* parent = 0);
    virtual ~CelestialObject();
    
    virtual void create(Ogre::SceneManager* manager, Ogre::SceneNode* node, const ObjectType& type);
    
    Real rotationSpeed() const;
    void setRotationSpeed(Real speed);
    
    Real revolutionSpeed() const;
    void setRevolutionSpeed(Real speed);
    
    Real size() const;
    void setSize(Real size);
    
    Real lightIntensity() const;
    void setLightIntensity(Real intensity);
    
private:
    Real mRotationSpeed;
    Real mRevolutionSpeed;
    Real mSize;
    Real mLightIntensity;
    Ogre::Light* mLight;
};

}

#endif // SPACE_CELESTIALOBJECT_H
