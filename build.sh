#!/bin/sh

brew install boost sfml sdl2
cmake -S server -B server
cmake -S client -B client
cmake -S client/graphicLibraries/ncurses -B client/graphicLibraries/ncurses
cmake -S client/graphicLibraries/sfml -B client/graphicLibraries/sfml
cmake -S client/graphicLibraries/sdl2 -B client/graphicLibraries/sdl2
make -C server -j4
make -C client -j4
make -C client/graphicLibraries/ncurses -j4
make -C client/graphicLibraries/sfml -j4
make -C client/graphicLibraries/sdl2 -j4
export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.5.1/lib
