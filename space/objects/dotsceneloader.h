#ifndef SPACE_DOTSCENELOADER_H
#define SPACE_DOTSCENELOADER_H
 
#include <OgreString.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>

#include "core/types.h"

#include <vector>
 
class TiXmlElement;

namespace Ogre
{
    // Forward declarations
    class SceneManager;
    class SceneNode;   
}

namespace Space
{
    class nodeProperty
    {
    public:
        String nodeName;
        String propertyNm;
        String valueName;
        String typeName;
 
        nodeProperty(const String &node, const String &propertyName, const String &value, const String &type)
            : nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
    };
 
    class DotSceneLoader
    {
    public:
        DotSceneLoader() : mSceneMgr(0) {}
        virtual ~DotSceneLoader() {}
 
        void parseDotScene(const String &SceneName, const String &groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *pAttachNode = NULL, const String &sPrependNode = "");
        String getProperty(const String &ndNm, const String &prop);
 
        std::vector<nodeProperty> nodeProperties;
        std::vector<String> staticObjects;
        std::vector<String> dynamicObjects;
 
    protected:
        void processScene(TiXmlElement *XMLRoot);
 
        void processNodes(TiXmlElement *XMLNode);
        void processExternals(TiXmlElement *XMLNode);
        void processEnvironment(TiXmlElement *XMLNode);
        void processTerrain(TiXmlElement *XMLNode);
        void processUserDataReference(TiXmlElement *XMLNode, Ogre::SceneNode *pParent = 0);
        void processUserDataReference(TiXmlElement *XMLNode, Ogre::Entity *pEntity);
        void processOctree(TiXmlElement *XMLNode);
        void processLight(TiXmlElement *XMLNode, Ogre::SceneNode *pParent = 0);
        void processCamera(TiXmlElement *XMLNode, Ogre::SceneNode *pParent = 0);
 
        void processNode(TiXmlElement *XMLNode, Ogre::SceneNode *pParent = 0);
        void processLookTarget(TiXmlElement *XMLNode, Ogre::SceneNode *pParent);
        void processTrackTarget(TiXmlElement *XMLNode, Ogre::SceneNode *pParent);
        void processEntity(TiXmlElement *XMLNode, Ogre::SceneNode *pParent);
        void processParticleSystem(TiXmlElement *XMLNode, Ogre::SceneNode *pParent);
        void processBillboardSet(TiXmlElement *XMLNode, Ogre::SceneNode *pParent);
        void processPlane(TiXmlElement *XMLNode, Ogre::SceneNode *pParent);
 
        void processFog(TiXmlElement *XMLNode);
        void processSkyBox(TiXmlElement *XMLNode);
        void processSkyDome(TiXmlElement *XMLNode);
        void processSkyPlane(TiXmlElement *XMLNode);
        void processClipping(TiXmlElement *XMLNode);
 
        void processLightRange(TiXmlElement *XMLNode, Ogre::Light *pLight);
        void processLightAttenuation(TiXmlElement *XMLNode, Ogre::Light *pLight);
 
        String getAttrib(TiXmlElement *XMLNode, const String &parameter, const String &defaultValue = "");
        Real getAttribReal(TiXmlElement *XMLNode, const String &parameter, Real defaultValue = 0);
        bool getAttribBool(TiXmlElement *XMLNode, const String &parameter, bool defaultValue = false);
 
        Ogre::Vector3 parseVector3(TiXmlElement *XMLNode);
        Ogre::Quaternion parseQuaternion(TiXmlElement *XMLNode);
        Ogre::ColourValue parseColour(TiXmlElement *XMLNode);
 
 
        Ogre::SceneManager *mSceneMgr;
        Ogre::SceneNode *mAttachNode;
        String m_sGroupName;
        String m_sPrependNode;
    };
}
 
#endif // SPACE_DOTSCENELOADER_H