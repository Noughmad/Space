project(space)

set (CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake")

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

find_package(Qt COMPONENTS QtCore REQUIRED)

add_subdirectory(space)
add_subdirectory(app)