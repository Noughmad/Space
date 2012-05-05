#include <string>

#include <OgreVector3.h>

#include <QMap>

#include "space_export.h"

namespace Ogre {
class SceneNode;
}

namespace Space
{

class Object;

typedef Ogre::String String;
typedef Ogre::Real Real;

typedef Ogre::Vector3 Coordinates;

typedef QMap<Object*, Ogre::SceneNode*> ObjectMap;

}