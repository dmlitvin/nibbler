find_package(Boost REQUIRED)

set(CLIENT_EXECUTABLE_NAME "${PROJECT_NAME}_client")

message(STATUS "Client executable name: ${CLIENT_EXECUTABLE_NAME}")

set(SRCS testClient.cpp DLLHandler.cpp)

add_executable(${CLIENT_EXECUTABLE_NAME})
target_sources(${CLIENT_EXECUTABLE_NAME}
	PRIVATE ${SRCS})

target_compile_features(${CLIENT_EXECUTABLE_NAME}
	PRIVATE cxx_std_17)

target_compile_options(${CLIENT_EXECUTABLE_NAME}
	PRIVATE -Wall
	PRIVATE -Wextra
	PRIVATE -Werror)

target_link_libraries(${CLIENT_EXECUTABLE_NAME} PRIVATE ${CURSES_LIBRARIES})
target_include_directories(${CLIENT_EXECUTABLE_NAME} PRIVATE ${CURSES_INCLUDE_DIR})

target_link_libraries(${CLIENT_EXECUTABLE_NAME} PRIVATE ${Boost_LIBRARIES})
target_include_directories(${CLIENT_EXECUTABLE_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

add_subdirectory(graphicLibraries)