cmake_minimum_required(VERSION 3.14)

project(NibblerServer)

set(CMAKE_CXX_STANDARD 17)

set(srcs Server.cpp tests.cpp)

find_package(Boost REQUIRED)

add_executable(exec ${srcs})

target_link_libraries(exec ${Boost_LIBRARIES})
target_include_directories(exec PUBLIC ${Boost_INCLUDE_DIRS})