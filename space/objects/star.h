#ifndef SPACE_STAR_H
#define SPACE_STAR_H

#include "celestialobject.h"


namespace Space {

class Star : public CelestialObject
{

public:
    Star(const String& name, Object* parent = 0);
    virtual ~Star();
};

}

#endif // SPACE_STAR_H
