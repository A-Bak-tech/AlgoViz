cmake_minimum_required(VERSION 3.20)
project(AlgoViz C CXX)
set(CMAKE_CXXSTANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(algoviz ${SOURCES})
target_include_directories(algoviz PRIVATE src)
target_link_libraries(algoviz PRIVATE raylib)