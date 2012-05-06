
set (space_SRCS 
    string.cpp 
    objecttype.cpp 
    object.cpp    
    objects/celestialobject.cpp 
    objects/planet.cpp 
    objects/star.cpp

    movementmanager.cpp
    application.cpp
    application_ogre.cpp
    scene.cpp
)

configure_file(space_config.h.in space_config.h)
    
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_QTCORE_INCLUDE_DIR} 
    ${OGRE_INCLUDE_DIR} 
    ${OIS_INCLUDE_DIR} 
    /usr/include/CEGUI
)

add_library(Space SHARED ${space_SRCS})
target_link_libraries(Space ${OGRE_LIBRARY} ${QT_QTCORE_LIBRARY} CEGUIBase CEGUIOgreRenderer)

install(TARGETS Space 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT SPACE
)

add_subdirectory(data)