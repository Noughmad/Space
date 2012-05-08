set (Space_Objects_SRCS
    star.cpp
    planet.cpp
    asteroidbelt.cpp 
    ship.cpp
)

set (Space_Objects_LIBS ${QT_QTCORE_LIBRARY} ${OGRE_MAIN_LIBRARY})

if (WITH_TINYXML)
    set (Space_Objects_SRCS 
        ${Space_Objects_SRCS}
        dotsceneobject.cpp
        dotsceneloader.cpp
    )
    set (Space_Objects_LIBS
        ${Space_Objects_LIBS}
        ${TINYXML_LIBRARIES}
    )
endif ()

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_definitions(-DBUILD_SPACE_CORE_LIBRARY)

add_library(SpaceObjects SHARED ${Space_Objects_SRCS})
target_link_libraries(SpaceObjects ${Space_Objects_LIBS})

install(TARGETS SpaceObjects
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT Objects
)
