#include <iostream>

#include <OgreException.h>

#include "space/application.h"
#include "space/objects/planet.h"
#include "space/objects/star.h"

using namespace Space;

int main(int argc, char *argv[])
{
    Application app;
    
    Star* star = new Star("Sun");
    star->setPosition(Coordinates(0, 0, 0));
    star->setSize(10);
    star->setRevolutionSpeed(0.01);
    star->setRotationSpeed(20.0);
    star->setLightIntensity(1.0);
    app.addObject(star);
    
    Planet* planet = new Planet("Earth", star);
    planet->setPosition(Coordinates(400.0, 0.0, 0.0));
    planet->setSize(2.4);
    planet->setRotationSpeed(0.8);
    planet->setRevolutionSpeed(2.8);
    app.addObject(planet);
    
    planet = new Planet("Mars", star);
    planet->setPosition(Coordinates(500.0, 100.0, 0.0));
    planet->setSize(1.9);
    planet->setRotationSpeed(1.6);
    planet->setRevolutionSpeed(1.8);
    app.addObject(planet);
 
    try 
    {
        app.start();
    } catch( Ogre::Exception& e ) {

    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }
    
    return 0;
}