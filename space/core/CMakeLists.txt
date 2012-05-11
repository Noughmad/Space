set (Space_Core_SRCS rotationmanager.cpp imovementmanager.cpp
    iobject.cpp
    iobjectfactory.cpp
    objectmanager.cpp
    application.cpp
    application_ogre.cpp
    
    luastate.cpp
    lua_space_core.cpp
)

set_source_files_properties(lua_space_core.cpp PROPERTIES GENERATED 1)

configure_file(space_config.h.in space_config.h)

set (SCRIPTED_FILES
    iobject.h
    objectmanager.h
)
generate_tolua_bindings(space_core space_core.pkg ${SCRIPTED_FILES})
message(${OGRE_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${OGRE_INCLUDE_DIR} ${CEGUI_INCLUDE_DIR} ${OIS_INCLUDE_DIR})
add_definitions(-DBUILD_SPACE_CORE_LIBRARY)

add_library(SpaceCore SHARED ${Space_Core_SRCS})
target_link_libraries(SpaceCore ${OGRE_LIBRARIES} ${CEGUI_BASE_LIBRARY} ${CEGUI_OGRE_RENDERER_LIBRARY} ${LUA_LIBRARIES} tolua++)


install(TARGETS SpaceCore
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT Core
)