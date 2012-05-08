#include "dotsceneobject.h"
#include "dotsceneloader.h"
#include <OgreSceneNode.h>

using namespace Space;

DotSceneObject::DotSceneObject(const Space::String& identifier, Space::IObject* parent) : IObject(identifier, parent)
{

}

DotSceneObject::~DotSceneObject()
{

}

Ogre::SceneNode* DotSceneObject::create(Ogre::SceneManager* manager, Ogre::SceneNode* node)
{
    Ogre::SceneNode* subNode = node->createChildSceneNode(id() + "/Node");
    
    String sceneFile;
    if (propertyNames().contains("SceneFileName"))
    {
        sceneFile = getProperty<String>("SceneFileName");
    }
    else
    {
        sceneFile = getProperty<String>("SubType") + ".scene";
        Ogre::StringUtil::toLowerCase(sceneFile);
    }
    
    DotSceneLoader loader;
    loader.parseDotScene(sceneFile, "Objects", manager, subNode, id() + "/");
    
    return subNode;
}

Space::String DotSceneObject::typeId() const
{
    return "Data";
}
