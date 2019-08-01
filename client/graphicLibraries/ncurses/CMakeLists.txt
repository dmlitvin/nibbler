cmake_minimum_required(VERSION 3.9)

project(ncursesNibbler C)

add_library(ncursesNibbler SHARED ncurses.c)

target_link_libraries(ncursesNibbler ncurses)
