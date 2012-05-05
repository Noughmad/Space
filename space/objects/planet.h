#ifndef SPACE_PLANET_H
#define SPACE_PLANET_H

#include "celestialobject.h"


namespace Space {

class Planet : public CelestialObject
{

public:
    Planet(const String& name, Object* parent = 0);
    virtual ~Planet();
};

}

#endif // SPACE_PLANET_H
