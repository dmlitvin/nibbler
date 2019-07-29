#include "DLLHandler.hpp"
#include <iostream>
#include <string>

int     main()
{
    std::cout << std::endl;

    std::string ncursesLib("/Users/dmlitvin/dump/dllhandler/ncurselib.dll");

    DLLHandler  *handler = new DLLHandler(ncursesLib, 10, 10);

    handler->init();
    handler->setGrid(0);
//    handler->draw();
//    handler->destroy();
//    handler->changeLibrary("sdl");
    handler->getLastPressed();
    handler->changeLibrary(ncursesLib);

    while (true)
        handler->draw();

    delete handler;

    std::cout << std::endl;

    system("leaks dll");

    return 0;
}
