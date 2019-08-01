#include "DLLHandler.hpp"

void    DLLHandler::draw()
{
    void(*funcDraw)() = reinterpret_cast<void(*)()>(functions["draw"]); funcDraw();
}

void    DLLHandler::setGrid(uint8_t *grid)
{
    std::cout << "setting grid" << std::endl;

    void(*ptrSetGrid)(uint8_t*) = reinterpret_cast<void(*)(uint8_t*)>(functions["setGrid"]); ptrSetGrid(grid);
}

void    DLLHandler::init()
{
    void(*ptrInit)(uint8_t, uint8_t) = reinterpret_cast<void(*)(uint8_t, uint8_t)>(functions["init"]); ptrInit(width, height);
}

void    DLLHandler::changeLibrary(std::string const &libPath)
{
    if (libPath == currLib)
        return ;
    std::cout << "changing dynamic library to " << libPath << std::endl;

    destroy();
    dlclose(dllPtr);
    loadLib(libPath);

    std::cout << "dynamic library changed to " << libPath << std::endl;
    currLib = libPath;

    init();
}

void    DLLHandler::destroy()
{
    void(*ptrDestroy)() = reinterpret_cast<void(*)()>(functions["destroy"]); ptrDestroy();

    std::cout << "destroying window" << std::endl;
}

DLLHandler::DLLHandler(std::string const &libPath, uint8_t width, uint8_t height)
: dllPtr(dlopen(libPath.c_str(), RTLD_LAZY)), width(width), height(height), currLib(libPath)
{
    std::cout << "constructing dllhandler with lib: " << libPath << std::endl;

    loadLib(libPath);

    std::cout << "lib: " << libPath << " constructed" << std::endl;
}

void    DLLHandler::loadLib(const std::string &libPath)
{
    std::cout << "loading graphic library " << libPath << std::endl;

    if (!(dlopen(libPath.c_str(), RTLD_LAZY)))
    {
        std::cerr << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto & strFunc : functions)
        if (!(strFunc.second = dlsym(dllPtr, strFunc.first.c_str())))
            std::cerr << dlerror() << std::endl;

    std::cout << "graphic library " << libPath << " loaded" << std::endl;
}

DLLHandler::~DLLHandler()
{
    dlclose(dllPtr);
}

key     DLLHandler::getLastPressed()
{
    key(*ptrGetLastPressed)() = reinterpret_cast<key(*)()>(functions["getLastPressed"]); lastPressed = ptrGetLastPressed();

    static std::map<key, std::string>  keyStr = {{UP, "UP"}, {DOWN, "DOWN"}, {LEFT, "LEFT"}, {RIGHT, "RIGHT"}};

    return lastPressed;
}
