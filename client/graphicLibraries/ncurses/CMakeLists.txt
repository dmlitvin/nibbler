find_package(Curses REQUIRED)

set(NCURSES_LIB "ncursesNibbler")
set(SRCS ncurses.c)

add_library(${NCURSES_LIB} SHARED)
target_sources(${NCURSES_LIB}
		PRIVATE ${SRCS})

target_compile_features(${NCURSES_LIB}
		PRIVATE cxx_std_17)
target_compile_options(${NCURSES_LIB}
		PRIVATE -Wall
		PRIVATE -Wextra
		PRIVATE -Werror)

target_link_libraries(${NCURSES_LIB}
		PRIVATE ncurses)
