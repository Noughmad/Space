#include <iostream>

#include <OgreException.h>

#include "core/application.h"

#include "objects/star.h"
#include "objects/planet.h"
#include <objects/ship.h>
#include <objects/asteroidbelt.h>

#include "core/objectmanager.h"
#include <core/luastate.h>

using namespace Space;

int main(int argc, char *argv[])
{
    LuaState state;
    
    
    ObjectManager& manager = ObjectManager::getSingleton();
    manager.registerFactory("Celestial/Star", new StarFactory());
    manager.registerFactory("Celestial/Planet", new PlanetFactory());
    manager.registerFactory("Celestial/Belt", new AsteroidBeltFactory());
    manager.registerFactory("Ship", new ShipFactory());
    
    
    ObjectList objects = state.loadObjects("galaxy.lua");
    
    if (objects.size() == 0)
    {
        return 0;
    }
    
    Application app;

    for (auto it = objects.cbegin(); it != objects.cend(); ++it)
    {
        std::cout << "Adding object " << (*it)->identifier() << std::endl;
        app.addObject(*it);
    }
 
    try 
    {
        app.start();
    } catch( Ogre::Exception& e ) {

    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }
        
    return 0;
}