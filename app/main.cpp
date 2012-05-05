#include <iostream>
#include "TutorialApplication.h"
#include "space/application.h"
#include <space/object.h>

using namespace Space;

int main(int argc, char *argv[])
{
    Application app;
    
    Object* star = new Object("Star", "Sun");
    star->setPosition(Coordinates(0, 0, 0));
    app.addObject(star);
    
    Object* planet = new Object("Planet", "Earth", star);
    planet->setPosition(Coordinates(20.0, -50.0, 0.0));
    app.addObject(planet);
 
    try 
    {
        app.start();
    } catch( Ogre::Exception& e ) {

    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }
    
    return 0;
}