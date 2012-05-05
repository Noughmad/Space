#include "planet.h"

using namespace Space;

Planet::Planet(const Space::String& name, Space::Object* parent) : CelestialObject("Planet", name, parent)
{
    setLightIntensity(0.0);
}

Planet::~Planet()
{

}