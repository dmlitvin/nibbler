cmake_minimum_required(VERSION 3.9)

project(sdl2Nibbler)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

add_library(sdl2Nibbler SHARED sdl2.cpp)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(sdl2Nibbler ${SDL2_LIBRARIES})
