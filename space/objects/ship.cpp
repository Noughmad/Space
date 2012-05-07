#include "ship.h"

using namespace Space;

Ship::Ship(const Space::String& identifier, Space::IObject* parent) : IObject(identifier, parent)
{

}

Ship::~Ship()
{

}

Ogre::SceneNode* Ship::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Q_ASSERT(false);
    return 0;
}

Space::String Ship::typeId() const
{
    return "Ship";
}
