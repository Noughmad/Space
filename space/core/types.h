#ifndef SPACE_TYPES_H
#define SPACE_TYPES_H

#include <OgrePrerequisites.h>

namespace Ogre {
class SceneNode;
}

namespace Space
{

class IObject;
    typedef Ogre::Real Real;
    typedef Ogre::String String;
    
    template <typename T> struct List
    { 
        typedef typename Ogre::list<T>::type type;
        typedef typename Ogre::list<T>::iterator iterator;
        typedef typename Ogre::list<T>::const_iterator const_iterator;
    };
    template <typename T> struct Set
    { 
        typedef typename Ogre::set<T>::type type;
        typedef typename Ogre::set<T>::iterator iterator;
        typedef typename Ogre::set<T>::const_iterator const_iterator;
    };
    
    template <typename K, typename V, typename P = std::less<K> >
    struct Map 
    { 
        typedef typename Ogre::map<K, V, P>::type type;
        typedef typename Ogre::map<K, V, P>::iterator iterator;
        typedef typename Ogre::map<K, V, P>::const_iterator const_iterator;
    };
    
    typedef List<String>::type StringList;
    typedef Set<String>::type StringSet;
    typedef Map<String, String>::type StringMap;
    typedef Set<IObject*>::type ObjectSet;
    typedef List<IObject*>::type ObjectList;
    
    typedef Map<IObject*, Ogre::SceneNode*>::type ObjectNodeMap;
    typedef Map<Ogre::SceneNode*, IObject*>::type NodeObjectMap;
}

#endif // SPACE_TYPES_H