#include <curses.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "../../key.h"

uint8_t *grid = NULL;
WINDOW  *win = NULL;
char    lastPressed = -1;

void    init(uint8_t width, uint8_t height)
{
    initscr();
    noecho();
    curs_set(FALSE);

    timeout(5);

    WINDOW *window = newwin(width, height, 0, 0);
}

void    setGrid(uint8_t *gridParam)
{
    grid = gridParam;
}

void    draw()
{
    char ch = getch();
    if (ch != -1)
        lastPressed = ch;

    mvprintw(0, 0, "Hello, world! char: %c", lastPressed);
    mvprintw(1, 1, "drawing from ncurses with gridPtr: %p", grid);
    refresh();
    usleep(10000);
}

enum key     getLastPressed()
{
    return lastPressed;
}

void    destroy()
{
    endwin();
}
