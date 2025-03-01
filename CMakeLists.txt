cmake_minimum_required(VERSION 3.21)

project(P88l VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(COPY media DESTINATION ${CMAKE_BINARY_DIR})

add_executable(P88l src/main.cpp src/Ball.cpp src/FPSCounter.cpp src/Game.cpp src/Menu.cpp src/Pockets.cpp src/Table.cpp src/Trajectory.cpp src/UI.cpp)
target_compile_features(P88l PRIVATE cxx_std_20)
target_link_libraries(P88l PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
