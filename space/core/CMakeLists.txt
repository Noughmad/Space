set (Space_Core_SRCS objectmanager.cpp
    string.cpp
    iobject.cpp
    iobjectfactory.cpp
    objectmanager.cpp
)

include_directories(${QT_INCLUDES})
add_definitions(-DBUILD_SPACE_CORE_LIBRARY)

add_library(SpaceCore SHARED ${Space_Core_SRCS})
target_link_libraries(SpaceCore ${QT_QTCORE_LIBRARY})

install(TARGETS SpaceCore
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT Core
)