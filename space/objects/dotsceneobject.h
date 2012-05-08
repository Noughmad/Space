#include "core/iobject.h"
#include "core/iobjectfactory.h"


namespace Space {

class DotSceneObject : public Space::IObject
{

public:
    DotSceneObject(const Space::String& identifier, Space::IObject* parent = 0);
    virtual ~DotSceneObject();

    virtual Ogre::SceneNode* create(Ogre::SceneManager* manager, Ogre::SceneNode* node);
    virtual Space::String typeId() const;
};

SPACE_DECLARE_FACTORY("Data", DotSceneObject)

}

