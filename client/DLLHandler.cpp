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

    destroy();
    dlclose(dllPtr);

    std::cout << "changing dynamic library to " << libPath << std::endl;

    loadLib(libPath);
    currLib = libPath;

    std::cout << "dynamic library changed to " << currLib << std::endl;
}

void    DLLHandler::destroy()
{
    void(*ptrDestroy)() = reinterpret_cast<void(*)()>(functions["destroy"]); ptrDestroy();

    std::cout << "destroying window" << std::endl;
}

DLLHandler::DLLHandler(std::string const &libPath, uint8_t* gridPtr, uint8_t width, uint8_t height)
: width(width), height(height), currLib(""), gridPtr(gridPtr)
{
    std::cout << "constructing dllhandler with lib: " << libPath << std::endl;

    loadLib(libPath);

    std::cout << "lib: " << libPath << " constructed" << std::endl;
}

void    DLLHandler::loadLib(const std::string &libPath)
{
    std::cout << "loading graphic library " << libPath << std::endl;

    if (!(dllPtr = dlopen(libPath.c_str(), RTLD_LAZY)))
    {
        std::cerr << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto & strFunc : functions)
        if (!(functions[strFunc.first] = dlsym(dllPtr, strFunc.first.c_str())))
            std::cerr << dlerror() << std::endl;

    std::cout << "graphic library " << libPath << " loaded" << std::endl;

    setGrid(gridPtr);
    init();
}

key     DLLHandler::getLastPressed()
{
    key(*ptrGetLastPressed)() = reinterpret_cast<key(*)()>(functions["getLastPressed"]); lastPressed = ptrGetLastPressed();

    static std::map<key, std::string>  keyStr = {{UP, "UP"}, {DOWN, "DOWN"}, {LEFT, "LEFT"}, {RIGHT, "RIGHT"}};

    return lastPressed;
}

DLLHandler::~DLLHandler()
{
    dlclose(dllPtr);
}
