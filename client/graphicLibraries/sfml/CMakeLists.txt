cmake_minimum_required(VERSION 3.9)

project(sfmlNibbler)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML COMPONENTS window graphics system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_library(sfmlNibbler SHARED sfml.cpp)

target_link_libraries(sfmlNibbler sfml-graphics sfml-window sfml-system)
