
#include_directories(${SFML_INCLUDE_DIR})

set(SRCS sfml.cpp)

set(SFML_LIB "sfmlNibbler")

add_library(${SFML_LIB} SHARED)
target_sources(${SFML_LIB}
		PRIVATE ${SRCS})

target_compile_features(${SFML_LIB}
		PRIVATE cxx_std_17)
target_compile_options(${SFML_LIB}
		PRIVATE -Wall
		PRIVATE -Wextra
		PRIVATE -Werror)

target_link_libraries(${SFML_LIB}
		PRIVATE sfml-graphics
		PRIVATE sfml-window
		PRIVATE sfml-system)

target_include_directories(${SFML_LIB}
		PRIVATE ${SFML_INCLUDE_DIR})

