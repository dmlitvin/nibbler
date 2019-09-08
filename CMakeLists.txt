cmake_minimum_required(VERSION 3.14)

project(nibbler VERSION 0.0.1)

find_package(Boost REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SFML COMPONENTS window graphics system REQUIRED)
find_package(Curses REQUIRED)

add_subdirectory(server)
add_subdirectory(client)

