cmake_minimum_required(VERSION 3.14)

project(Nibbler)

set(CMAKE_CXX_STANDARD 17)

set(srcs Server.cpp ClientController.cpp Snake.cpp GameBoard.cpp ComputerController.cpp DLLHandler.cpp main.cpp)

find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} ${srcs})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})