#include <iostream>

#include <OgreException.h>

#include "space/application.h"
#include "space/objects/celestialobject.h"

using namespace Space;

int main(int argc, char *argv[])
{
    Application app;
    
    ObjectType starType;
    starType.identifier = "Star/Yellow";
    starType.mesh = "Star.mesh";
    starType.material = "StellarMatter.material";
    app.registerObjectType(starType);
    
    ObjectType planetType;
    planetType.identifier = "Planet/Earth";
    planetType.mesh = "Planet.mesh";
    planetType.material = "Earth.material";
    app.registerObjectType(planetType);
    
    CelestialObject* star = new CelestialObject(starType.identifier, "Sun");
    star->setPosition(Coordinates(0, 0, 0));
    star->setSize(10);
    star->setRevolutionSpeed(0.01);
    star->setRotationSpeed(4.0);
    star->setLightIntensity(1.0);
    app.addObject(star);
    
    CelestialObject* planet = new CelestialObject(planetType.identifier, "Earth", star);
    planet->setPosition(Coordinates(400.0, 0.0, 0.0));
    planet->setSize(2.4);
    planet->setRotationSpeed(10);
    planet->setRevolutionSpeed(0.1);
    app.addObject(planet);
    
    planet = new CelestialObject(planetType.identifier, "Mars", star);
    planet->setPosition(Coordinates(500.0, 100.0, 0.0));
    planet->setSize(1.9);
    planet->setRotationSpeed(13);
    planet->setRevolutionSpeed(0.06);
    app.addObject(planet);
 
    try 
    {
        app.start();
    } catch( Ogre::Exception& e ) {

    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }
    
    return 0;
}