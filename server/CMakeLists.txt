find_package(Boost REQUIRED)

set(SERVER_EXECUTABLE_NAME "${PROJECT_NAME}_server")
set(SRCS Server.cpp ClientController.cpp Snake.cpp GameBoard.cpp main.cpp ComputerController.cpp)

message(STATUS "Server executable name: ${SERVER_EXECUTABLE_NAME}")

add_executable(${SERVER_EXECUTABLE_NAME})

target_compile_features(${SERVER_EXECUTABLE_NAME}
		PRIVATE cxx_std_17)
target_compile_options(${SERVER_EXECUTABLE_NAME}
		PRIVATE -Wall
		PRIVATE -Wextra
		PRIVATE -Werror)

target_sources(${SERVER_EXECUTABLE_NAME}
		PRIVATE ${SRCS})

target_link_libraries(${SERVER_EXECUTABLE_NAME} PRIVATE ${Boost_LIBRARIES})
target_include_directories(${SERVER_EXECUTABLE_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
