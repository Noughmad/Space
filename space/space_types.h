#ifndef SPACE_TYPES_H
#define SPACE_TYPES_H

#include <string>

#include <OgreVector3.h>

#include <QMap>
#include <QString>

#include "space_export.h"

namespace Ogre {
class SceneNode;
}

namespace Space
{

class IObject;

typedef Ogre::Real Real;

typedef Ogre::Vector3 Coordinates;

typedef QMap<IObject*, Ogre::SceneNode*> ObjectMap;

}

#endif // SPACE_TYPES_H