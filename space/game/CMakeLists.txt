set (Space_Game_SRCS
    player.cpp
    gamecontroller.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/.. ${OGRE_INCLUDE_DIR})
add_definitions(-DBUILD_SPACE_GAME_LIBRARY)

add_library(SpaceGame SHARED ${Space_Game_SRCS})
target_link_libraries(SpaceGame SpaceCore)

install(TARGETS SpaceGame
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT Game
)
