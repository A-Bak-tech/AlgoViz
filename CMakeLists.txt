cmake_minimum_required(VERSION 3.20)
project(AlgoViz C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (EMSCRIPTEN)
  set(PLATFORM Web CACHE STRING "" FORCE)
endif()

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

if (EMSCRIPTEN)
  set_target_properties(algoviz PROPERTIES OUTPUT_NAME "index" SUFFIX ".html")
  target_link_options(algoviz PRIVATE
    -sUSE_GLFW=3
    -sASYNCIFY
    -sALLOW_MEMORY_GROWTH=1
    "--shell-file=${CMAKE_SOURCE_DIR}/web/shell.html")
endif()