#include "DLLHandler.hpp"

void    DLLHandler::draw()
{
    void(*funcDraw)() = reinterpret_cast<void(*)()>(functions["draw"]); funcDraw();
}

void    DLLHandler::setGrid(uint8_t *grid)
{
	std::cout << "setGrid()..." << std::endl;

	void(*ptrSetGrid)(uint8_t*) = reinterpret_cast<void(*)(uint8_t*)>(functions["setGrid"]); ptrSetGrid(grid);
	std::cout << "setGrid() done" << std::endl;
}

void    DLLHandler::init(key initKey)
{
	std::cout << "ptrInit()..." << std::endl;
    void(*ptrInit)(uint8_t, uint8_t, key) = reinterpret_cast<void(*)(uint8_t, uint8_t, key)>(functions["init"]); ptrInit(width, height, initKey);
    std::cout << "ptrInit() done" << std::endl;
}

void    DLLHandler::changeLibrary(std::string const &libPath, key initKey)
{
    if (libPath == currLib)
        return ;

    destroy();
    dlclose(dllPtr);

    std::cout << "changing dynamic library to " << libPath << std::endl;

    loadLib(libPath, initKey);

    std::cout << "dynamic library changed to " << currLib << std::endl;
}

void    DLLHandler::destroy()
{
    void(*ptrDestroy)() = reinterpret_cast<void(*)()>(functions["destroy"]); ptrDestroy();

    std::cout << "destroying window" << std::endl;
}

DLLHandler::DLLHandler(std::string const &libPath, uint8_t* gridPtr, uint8_t width, uint8_t height)
: width(width), height(height), gridPtr(gridPtr), currLib("")
{
    std::cout << "constructing dllhandler with lib: " << libPath << std::endl;

    loadLib(libPath, key::RIGHT);

    std::cout << "lib: " << libPath << " constructed" << std::endl;
}

void    DLLHandler::loadLib(const std::string &libPath, key initKey)
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

	currLib = libPath;

    setGrid(gridPtr);
    init(initKey);
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
