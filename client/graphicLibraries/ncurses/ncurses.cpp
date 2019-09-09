#include <curses.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include <map>
#include <list>

#include "../../key.h"

namespace
{
    int      screenWidth, screenHeight;
    uint8_t  *grid = NULL, gridWidth, gridHeight;
    char     lastPressed;

    const char   *content = ".F?sSzZhHkKiIwWeE";
}

extern "C"
void    init(uint8_t width, uint8_t height, enum key initKey)
{
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    timeout(5);

    getmaxyx(stdscr, screenHeight, screenWidth);

    gridWidth = width;
    gridHeight = height;
    static const char buttons[] = {'w', 's', 'a', 'd'};
    lastPressed = buttons[initKey];
}

extern "C"
void    setGrid(uint8_t *gridParam)
{
    grid = gridParam;
}

extern "C"
void    destroy()
{
    curs_set(TRUE);
    system("clear");
    endwin();
}

extern "C"
void    draw()
{
    static const std::list<char>    buttonList = {'w', 'a', 's', 'd', '1', '2', '3'};
    char ch = getch();
    if (std::find(buttonList.begin(), buttonList.end(), ch) != buttonList.end())
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

extern "C"
enum key     getLastPressed()
{
    static const std::map<char, enum key>   char_key = {{'d', RIGHT},
                                                        {'a', LEFT},
                                                        {'w', UP},
                                                        {'s', DOWN},
                                                        {'1', NB1},
                                                        {'2', NB2},
                                                        {'3', NB3}};
    try
    {
        return char_key.at(lastPressed);
    }
    catch(...)
    {
        return RIGHT;
    }
}
