project(Space)

cmake_minimum_required(VERSION 2.6)

set (CMAKE_MODULE_PATH "${Space_SOURCE_DIR}/cmake" "/usr/lib/OGRE/cmake")

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(TinyXML REQUIRED)

find_package(CEGUI)
find_package(Lua51)
find_package(ToLua)

include(SpaceMacros)

set (WITH_TINYXML ${TINYXML_FOUND})

set (SPACE_DATA_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/Space")
set (SPACE_LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH "${SPACE_LIB_INSTALL_DIR}")

set (OGRE_PLUGIN_DIR ${OGRE_PLUGIN_DIR_TMP})

find_package(Qt COMPONENTS QtCore REQUIRED)

add_subdirectory(space)
add_subdirectory(app)
