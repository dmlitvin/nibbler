cmake_minimum_required(VERSION 3.14)

project(NibblerClient)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Werror")

set(srcs testClient.cpp DLLHandler.cpp)

find_package(SFML 2.5 REQUIRED system window graphics)
find_package(Boost REQUIRED)
find_package(Curses REQUIRED)

add_executable(${PROJECT_NAME} ${srcs})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CURSES_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
