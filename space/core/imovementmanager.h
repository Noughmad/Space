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

#ifndef SPACE_IMOVEMENTMANAGER_H
#define SPACE_IMOVEMENTMANAGER_H

#include "types.h"

// tolua_begin
namespace Space {

/**
 * @brief An interface for managing movement of space objects
 * 
 * Reasons for moving objects can be various. 
 * It can be the natural rotation and revolution of a many-body system, 
 * or it can be because of player-given orders. 
 * 
 * This is a thin interface with only one method. 
 * See the documentation for processFrame() for details. 
 **/
class IMovementManager
{
    // tolua_end
public:
    /**
     * Default destructor
     * 
     **/
    virtual ~IMovementManager();
    
    // tolua_begin
    /**
     * @brief Process one frame of the simulations
     * 
     * Implement this method to change the positions and orientations of all the objects in the simulation
     * that need to be moved. 
     *
     * @param sceneManager the scene manager
     * @param objects all the object in the scene
     * @param timeSinceLastFrame the period in the simulation since the last time this function was called
     **/
    virtual void processFrame(Ogre::SceneManager* sceneManager, ObjectNodeMap objects, Real timeSinceLastFrame) = 0;

};

}

// tolua_end

#endif // SPACE_IMOVEMENTMANAGER_H
