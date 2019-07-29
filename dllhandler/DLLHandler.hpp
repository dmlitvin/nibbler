#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <map>

#include <dlfcn.h>
#include "key.h"

struct DLLHandler
{

    explicit DLLHandler(std::string const & libPath, uint8_t, uint8_t);

    void    init();
    void    setGrid(uint8_t*);
    void    draw();
    void    destroy();

    void    changeLibrary(std::string const & libPath);

    key     getLastPressed();

    ~DLLHandler();

private:

    key                             lastPressed = key::RIGHT;

    void                            *dllPtr;
    std::map<std::string, void*>    functions = {{"init", nullptr},
                                                 {"setGrid", nullptr},
                                                 {"draw", nullptr},
                                                 {"destroy", nullptr},
                                                 {"getLastPressed", nullptr}};

    uint8_t width, height;

};
