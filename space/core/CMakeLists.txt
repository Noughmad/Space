set (Space_Core_SRCS objectmanager.cpp
    string.cpp
    iobject.cpp
    iobjectfactory.cpp
    objectmanager.cpp
    lua_space_core.cpp
)

set_source_files_properties(lua_space_core.cpp PROPERTIES GENERATED 1)
generate_tolua_bindings(space_core space_core.pkg)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DBUILD_SPACE_CORE_LIBRARY)

add_library(SpaceCore SHARED ${Space_Core_SRCS})
target_link_libraries(SpaceCore ${QT_QTCORE_LIBRARY} ${OGRE_LIBRARIES})


install(TARGETS SpaceCore
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT Core
)