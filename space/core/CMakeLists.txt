set (Space_Core_SRCS luastate.cpp
    iobject.cpp
    iobjectfactory.cpp
    objectmanager.cpp
    lua_space_core.cpp
)

set_source_files_properties(lua_space_core.cpp PROPERTIES GENERATED 1)
set (SCRIPTED_FILES
    iobject.h
    objectmanager.h
)
generate_tolua_bindings(space_core space_core.pkg ${SCRIPTED_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DBUILD_SPACE_CORE_LIBRARY)

add_library(SpaceCore SHARED ${Space_Core_SRCS})
target_link_libraries(SpaceCore ${OGRE_LIBRARIES} ${LUA_LIBRARIES} tolua++)


install(TARGETS SpaceCore
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT Core
)