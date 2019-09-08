set(SDL2_LIB "sdl2Nibbler")

set(SRCS sdl2.cpp Window.cpp Grid.cpp)

add_library(${SDL2_LIB} SHARED)
target_sources(${SDL2_LIB}
		PRIVATE ${SRCS})

target_compile_features(${SDL2_LIB}
		PRIVATE cxx_std_17)
target_compile_options(${SDL2_LIB}
		PRIVATE -Wall
		PRIVATE -Wextra
		PRIVATE -Werror)

target_link_libraries(${SDL2_LIB}
		PRIVATE ${SDL2_LIBRARIES})

target_include_directories(${SDL2_LIB}
		PRIVATE ${SDL2_INCLUDE_DIRS})
