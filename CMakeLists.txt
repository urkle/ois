CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(OIS)

SET(VERSION "1.4.0")

OPTION(ENABLE_SDL "Enable SDL Support" OFF)

include_directories(
    includes
)

IF(ENABLE_SDL)
    SET(PLATFORM_SOURCE
        src/SDL/SDLInputManager.cpp
        src/SDL/SDLJoyStick.cpp
        src/SDL/SDLKeyboard.cpp
        src/SDL/SDLMouse.cpp
    )
    FIND_PACKAGE(SDL REQUIRED)
    include_directories(
        ${SDL_INCLUDE_DIR}
    )
    SET(PLATFORM_LIBS
        ${SDL_LIBRARY}
    )
ELSE()
    SET(PLATFORM_SOURCE
        src/linux/EventHelpers.cpp
        src/linux/LinuxForceFeedback.cpp
        src/linux/LinuxInputManager.cpp
        src/linux/LinuxJoyStickEvents.cpp
        src/linux/LinuxKeyboard.cpp
        src/linux/LinuxMouse.cpp
    )
    SET(PLATFORM_LIBS
        X11
    )
ENDIF()

SET(OIS_SOURCE
    src/OISEffect.cpp
    src/OISException.cpp
    src/OISForceFeedback.cpp
    src/OISInputManager.cpp
    src/OISJoyStick.cpp
    src/OISKeyboard.cpp
    src/OISObject.cpp
)

SET(OIS_HEADERS
    includes/OISConfig.h
    includes/OISEffect.h
    includes/OISEvents.h
    includes/OISException.h
    includes/OISForceFeedback.h
    includes/OISInputManager.h
    includes/OISInterface.h
    includes/OISJoyStick.h
    includes/OISKeyboard.h
    includes/OISMouse.h
    includes/OISObject.h
    includes/OISPrereqs.h
    includes/OISFactoryCreator.h
    includes/OISMultiTouch.h
    includes/OIS.h
)

# OIS Shared Library
ADD_LIBRARY(OIS SHARED
    ${OIS_SOURCE}
    ${PLATFORM_SOURCE}
)
SET_TARGET_PROPERTIES(OIS
    PROPERTIES
        VERSION ${VERSION}
        SOVERSION ${VERSION}
)
TARGET_LINK_LIBRARIES(OIS
    ${PLATFORM_LIBS}
)

# OIS Static Library
ADD_LIBRARY(OIS_static STATIC
    ${OIS_SOURCE}
    ${PLATFORM_SOURCE}
)
SET_TARGET_PROPERTIES(OIS_static
    PROPERTIES
        OUTPUT_NAME "OIS"
)

# Demo Executables
ADD_EXECUTABLE(ConsoleTest
    demos/OISConsole.cpp
)
TARGET_LINK_LIBRARIES(ConsoleTest
    OIS
)

ADD_EXECUTABLE(FFConsoleTest
    demos/FFConsoleDemo.cpp
)
TARGET_LINK_LIBRARIES(FFConsoleTest
    OIS
)

SET(prefix ${CMAKE_INSTALL_PREFIX})
SET(exec_prefix "\${prefix}")
SET(libdir "\${prefix}/lib")
SET(includedir "\${prefix}/include")
SET(PACKAGE "OIS")
CONFIGURE_FILE(OIS.pc.in OIS.pc @ONLY)

INSTALL(TARGETS OIS OIS_static
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

INSTALL(FILES ${OIS_HEADERS} DESTINATION include/OIS)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/OIS.pc DESTINATION lib/pkgconfig)