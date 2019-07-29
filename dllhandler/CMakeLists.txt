project(dll)

set(CMAKE_CXX_FLAGS -std=c++11)

add_executable(dll main.cpp DLLHandler.cpp)
