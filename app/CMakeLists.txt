
set (galactomania_SRCS
    main.cpp
)
    
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../space ${QT_QTCORE_INCLUDE_DIR} ${OGRE_INCLUDE_DIR} ${OIS_INCLUDE_DIR})
add_executable(galactomania ${galactomania_SRCS})

target_link_libraries(galactomania Space SpaceCore SpaceObjects ${OGRE_LIBRARY} ${OIS_LIBRARY} ${QT_QTCORE_LIBRARY})

install(TARGETS galactomania 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION bin
    COMPONENT SPACE
)