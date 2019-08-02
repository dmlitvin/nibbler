#include <curses.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../key.h"

static int      screenWidth, screenHeight;
static uint8_t  *grid = NULL, gridWidth, gridHeight;
static WINDOW   *win = NULL;
static char     lastPressed = -1;

static const char   *content = ".F?sSzZhHkKiIwWeE";

void    init(uint8_t width, uint8_t height)
{
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    timeout(5);

    getmaxyx(stdscr, screenHeight, screenWidth);

    gridWidth = width;
    gridHeight = height;
}

void    setGrid(uint8_t *gridParam)
{
    grid = gridParam;
}

void    destroy()
{
    curs_set(TRUE);
    system("clear");
    endwin();
}

void    draw()
{
    char ch = getch();
    if (ch != -1)
        lastPressed = ch;

    if (ch == 27)
    {
        destroy();
        exit(EXIT_SUCCESS);
    }

    const int leftBorder = (screenWidth - gridWidth * 2) / 2;
    const int topBorder = (screenHeight - gridHeight) / 2;

    for (size_t y = 0; y < gridHeight; y++)
        for (size_t x = 0; x < gridWidth; x++)
            mvwprintw(stdscr, topBorder + y, leftBorder + x * 2, "%c", content[grid[y * gridWidth + x]]);

    refresh();
    usleep(10);
}

enum key     getLastPressed()
{
    if (lastPressed == 'd')
        return RIGHT;
    else if (lastPressed == 'a')
        return LEFT;
    else if (lastPressed == 'w')
        return UP;
    else if (lastPressed == 's')
        return DOWN;
    else if (lastPressed == '1')
        return NB1;
    else if (lastPressed == '2')
        return NB2;
    return RIGHT;
}
