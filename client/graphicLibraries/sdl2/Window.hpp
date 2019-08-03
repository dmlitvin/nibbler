
# include <iostream>
# include <string>
# include "../../key.h"
# include <SDL.h>

class Window
{
	int				width = 1920;
	int				height = 1000;
	std::string		name = "Window";
	SDL_Window		*window = nullptr;
	int				closed = false;
	useconds_t		speed = 35000;
	key				lastPressed;

public:

    Window() = delete;
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
	~Window();

	SDL_Renderer	*renderer = nullptr;
	Window(std::string name, int width, int height, key initKey);
	useconds_t GetSpeed();
	bool isClosed();
	key getLastPressed();
	void poolEvents();
	void clear();

};
