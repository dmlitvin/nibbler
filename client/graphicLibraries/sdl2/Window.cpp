#include "Window.hpp"

Window::Window(std::string name, int width, int height, key initKey)
{
	this->width = width;
	this->height = height;
	this->name = name;
	this->lastPressed = initKey;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_INIT_VIDEO::ERROR" << std::endl;
		closed = true;
		return ;
	}

	this->window = SDL_CreateWindow(this->name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			this->width,
			this->height,
            SDL_WINDOW_RESIZABLE);

	if (this->window == nullptr)
	{
		std::cerr << "CREATE_WINDOW::ERROR" << std::endl;
		closed = true;
		return ;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

	if (this->renderer == nullptr)
	{
		std::cerr << "CREATE_RENDERER::ERROR" << std::endl;
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

bool Window::isClosed()
{
	return (closed) ? true : false;
}

void Window::poolEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
			if (event.type == SDL_QUIT)
            {
				this->closed = true;
                exit(EXIT_SUCCESS);
            }
			else if (event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
                    case SDLK_ESCAPE: exit(EXIT_SUCCESS); break;
					case SDLK_a: lastPressed = key::LEFT; break;
					case SDLK_w: lastPressed = key::UP; break;
					case SDLK_d: lastPressed = key::RIGHT; break;
					case SDLK_s: lastPressed = key::DOWN; break;
                    
					case SDLK_1: lastPressed = key::NB1; break;
					case SDLK_2: lastPressed = key::NB2; break;
					case SDLK_3: lastPressed = key::NB3; break;
					default:
						break;
				}
			}
		}
	}

void Window::clear()
{
	SDL_RenderPresent(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);
}

key Window::getLastPressed()
{
	return lastPressed;
}