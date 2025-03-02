cmake_minimum_required(VERSION 3.21)

project(P88l VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# for Viual Studio
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# icon for Windows
if(WIN32)
	set(RESOURCE_FILE media/icon/resources.rc)
endif()

add_executable(P88l src/main.cpp src/Ball.cpp src/FPSCounter.cpp src/Game.cpp src/Menu.cpp src/Pockets.cpp src/Table.cpp src/Trajectory.cpp src/UI.cpp ${RESOURCE_FILE})
target_compile_features(P88l PRIVATE cxx_std_20)
target_link_libraries(P88l PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)

file(COPY media DESTINATION ${CMAKE_BINARY_DIR})

# don't open a console window on Windows
if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# copy openal32.dll to build\bin for Windows
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(OPENAL_DLL_PATH "${CMAKE_SOURCE_DIR}/extlibs/bin/x64/openal32.dll")
	else()
		set(OPENAL_DLL_PATH "${CMAKE_SOURCE_DIR}/extlibs/bin/x86/openal32.dll")
	endif()

	file(COPY ${OPENAL_DLL_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
