set (Space_Objects_SRCS
    star.cpp
    planet.cpp
)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/..)
add_definitions(-DBUILD_SPACE_CORE_LIBRARY)

add_library(SpaceObjects SHARED ${Space_Objects_SRCS})
target_link_libraries(SpaceObjects ${QT_QTCORE_LIBRARY})

install(TARGETS SpaceObjects
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT Objects
)
