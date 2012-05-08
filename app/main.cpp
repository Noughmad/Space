#include <iostream>

#include <OgreException.h>

#include "application.h"

#include "objects/star.h"
#include "objects/planet.h"

#include "core/objectmanager.h"

using namespace Space;

int main(int argc, char *argv[])
{
    Application app;
    
    ObjectManager& manager = ObjectManager::getSingleton();
    
    manager.registerFactory("Celestial/Star", new StarFactory());
    manager.registerFactory("Celestial/Planet", new PlanetFactory());
    
    IObject* star = manager.createObject("Celestial/Star/Yellow/Sun");
    star->setPosition(Ogre::Vector3(0, 0, 0));
    star->setProperty("Size", 10.0);
    star->setProperty("RotationSpeed", 2.0);
    app.addObject(star);
    
    IObject* object = manager.createObject("Celestial/Planet/Blue/Earth");
    object->setPosition(Ogre::Vector3(70, 0, 0));
    object->setParent(star);
    object->setProperty("Size", 2.6);
    object->setProperty("RotationSpeed", 1.0);
    object->setProperty("RevolutionSpeed", 0.1);
    app.addObject(object);
    
    object->setParent(star);
    object = manager.createObject("Celestial/Planet/Red/Mars");
    object->setPosition(Ogre::Vector3(80, 10, 0));
    object->setProperty("Size", 1.8);
    object->setProperty("RotationSpeed", 1.3);
    object->setProperty("RevolutionSpeed", 0.06);
    app.addObject(object);
 
    try 
    {
        app.start();
    } catch( Ogre::Exception& e ) {

    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }
    
    return 0;
}