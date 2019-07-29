#include "DLLHandler.hpp"

void    DLLHandler::draw()
{
    void(*funcDraw)() = reinterpret_cast<void(*)()>(functions["draw"]); funcDraw();

//    std::cout << "drawing" << std::endl;
}

void    DLLHandler::setGrid(uint8_t *grid)
{
    std::cout << "setting grid" << std::endl;

    void(*ptrSetGrid)(uint8_t*) = reinterpret_cast<void(*)(uint8_t*)>(functions["setGrid"]); ptrSetGrid(grid);
}

void    DLLHandler::init()
{
//    std::cout << "initing window with width " << (int)width << " and height " << (int)height << std::endl;

    void(*ptrInit)(uint8_t, uint8_t) = reinterpret_cast<void(*)(uint8_t, uint8_t)>(functions["init"]); ptrInit(width, height);
}

void    DLLHandler::changeLibrary(std::string const &libPath)
{
//    std::cout << "changing library to " << libPath << std::endl;

    destroy();
    dlclose(dllPtr);
    dllPtr = dlopen(libPath.c_str(), RTLD_LAZY);
    for (auto & mapPair : functions)
        if (!(mapPair.second = dlsym(dllPtr, mapPair.first.c_str())))
            std::cerr << dlerror() << std::endl;

//    std::cout << "library changed to " << libPath << std::endl;
    init();
}

void    DLLHandler::destroy()
{
    void(*ptrDestroy)() = reinterpret_cast<void(*)()>(functions["destroy"]); ptrDestroy();

//    std::cout << "destroying window" << std::endl;
}

DLLHandler::DLLHandler(std::string const &libPath, uint8_t width, uint8_t height)
: dllPtr(dlopen(libPath.c_str(), RTLD_LAZY)), width(width), height(height)
{
//    std::cout << "constructing dllhandler with lib: " << libPath << std::endl;

    for (auto & mapPair : functions)
        if (!(mapPair.second = dlsym(dllPtr, mapPair.first.c_str())))
            std::cerr << dlerror() << std::endl;

//    std::cout << "lib: " << libPath << "constructed" << std::endl;
}

DLLHandler::~DLLHandler()
{
//    std::cout << "destructing dllhandler" << std::endl;
    dlclose(dllPtr);
}

key     DLLHandler::getLastPressed()
{
    key(*ptrGetLastPressed)() = reinterpret_cast<key(*)()>(functions["getLastPressed"]); lastPressed = ptrGetLastPressed();

    static std::map<key, std::string>  keyStr = {{UP, "UP"}, {DOWN, "DOWN"}, {LEFT, "LEFT"}, {RIGHT, "RIGHT"}};
//    std::cout << "last pressed button: " << keyStr[lastPressed] << std::endl;

    return lastPressed;
}
