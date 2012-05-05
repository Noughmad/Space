
set (space_SRCS objects/celestialobject.cpp objects/planet.cpp objects/star.cpp
    movementmanager.cpp
    application.cpp
    scene.cpp
    object.cpp    
)
    
include_directories(${QT_QTCORE_INCLUDE_DIR} ${OGRE_INCLUDE_DIR} ${OIS_INCLUDE_DIR})
add_library(space SHARED ${space_SRCS})
target_link_libraries(space ${OGRE_LIBRARY} ${QT_QTCORE_LIBRARY})

install(TARGETS space 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT SPACE
)
