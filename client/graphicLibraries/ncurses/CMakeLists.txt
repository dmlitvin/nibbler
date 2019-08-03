cmake_minimum_required(VERSION 3.9)

project(ncursesNibbler C)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Werror")

add_library(ncursesNibbler SHARED ncurses.c)

target_link_libraries(ncursesNibbler ncurses)
