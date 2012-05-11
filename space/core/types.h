/*
 * Copyright 2012 Miha Čančula <miha@noughmad.eu>
 * This file is a part of Space, a library for space simulations
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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