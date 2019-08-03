#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <map>

#include <dlfcn.h>
#include "key.h"

struct DLLHandler
{

    explicit DLLHandler(std::string const & libPath, uint8_t*, uint8_t, uint8_t);

    void    init(key);
    void    setGrid(uint8_t*);
    void    draw();
    void    destroy();
    void    loadLib(const std::string & libPath, key);

    void    changeLibrary(std::string const & libPath, key);

    key     getLastPressed();

    ~DLLHandler();
    DLLHandler() = delete;
    DLLHandler(const DLLHandler&) = delete;
    DLLHandler& operator=(const DLLHandler&) = delete;

private:

    uint8_t width, height;

    key         lastPressed = key::RIGHT;
    uint8_t     *gridPtr;
    void        *dllPtr;
    std::string currLib;

    std::map<std::string, void*>    functions = {{"init", nullptr},
                                                 {"setGrid", nullptr},
                                                 {"draw", nullptr},
                                                 {"destroy", nullptr},
                                                 {"getLastPressed", nullptr}};

};
