#include <iostream>

#include <OgreException.h>

#include "application.h"

#include "objects/star.h"
#include "objects/planet.h"
#include <objects/ship.h>

#include "core/objectmanager.h"

using namespace Space;

int main(int argc, char *argv[])
{
    Application app;
    
    ObjectManager& manager = ObjectManager::getSingleton();
    
    manager.registerFactory("Celestial/Star", new StarFactory());
    manager.registerFactory("Celestial/Planet", new PlanetFactory());
    manager.registerFactory("Ship", new ShipFactory());
    
    IObject* star = manager.createObject("Celestial/Star/Yellow/Sun");
    star->setPosition(Ogre::Vector3(0, 0, 0));
    star->setProperty("Size", 10.0);
    star->setProperty("RotationSpeed", 2.0);
    app.addObject(star);
    
    IObject* earth = manager.createObject("Celestial/Planet/Blue/Earth");
    earth->setParent(star);
    earth->setPosition(Ogre::Vector3(70, 0, 0));
    earth->setProperty("Size", 2.6);
    earth->setProperty("RotationSpeed", 1.0);
    earth->setProperty("RevolutionSpeed", 0.1);
    app.addObject(earth);
    
    IObject* mars = manager.createObject("Celestial/Planet/Red/Mars");
    mars->setParent(star);
    mars->setPosition(Ogre::Vector3(80, 10, 0));
    mars->setProperty("Size", 1.8);
    mars->setProperty("RotationSpeed", 1.3);
    mars->setProperty("RevolutionSpeed", 0.06);
    app.addObject(mars);
    
    IObject* ship = manager.createObject("Ship/Probe/Voyager");
    ship->setParent(earth);
    ship->setPosition(Ogre::Vector3(4.0, 0.0, 0));
    ship->setProperty("RevolutionSpeed", 5.0);
    app.addObject(ship);
 
    try 
    {
        app.start();
    } catch( Ogre::Exception& e ) {

    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }
    
    return 0;
}