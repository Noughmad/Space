#include <iostream>

#include <OgreException.h>

#include "space/application.h"
#include "space/objects/celestialobject.h"

using namespace Space;

int main(int argc, char *argv[])
{
    Application app;
    
    CelestialObject* star = new CelestialObject("Celestial/Star/Yellow", "Sun");
    star->setPosition(Coordinates(0, 0, 0));
    star->setSize(10);
    star->setRevolutionSpeed(0.01);
    star->setRotationSpeed(4.0);
    star->setLightIntensity(1.0);
    app.addObject(star);
    
    CelestialObject* planet = new CelestialObject("Celestial/Planet/Earth", "Earth", star);
    planet->setPosition(Coordinates(400.0, 0.0, 0.0));
    planet->setSize(2.4);
    planet->setRotationSpeed(10);
    planet->setRevolutionSpeed(1);
    app.addObject(planet);
    
    planet = new CelestialObject("Celestial/Planet/Mars", "Mars", star);
    planet->setPosition(Coordinates(600.0, 0.0, 0.0));
    planet->setSize(1.9);
    planet->setRotationSpeed(13);
    planet->setRevolutionSpeed(0.6);
    app.addObject(planet);
 
    try 
    {
        app.start();
    } catch( Ogre::Exception& e ) {

    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }
    
    return 0;
}