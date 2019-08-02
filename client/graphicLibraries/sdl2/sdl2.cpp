/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:32:57 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/08/02 19:53:08 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <string>
# include "../../key.h"
# include <SDL2/SDL.h>

class Window
{
	int				width = 1920;
	int				height = 1000;
	std::string		name = "Window";
	SDL_Window		*window = nullptr;
	int				closed = false;
	useconds_t		speed = 35000;

	key				lastPressed = key::RIGHT;
public:
	SDL_Renderer	*renderer = nullptr;
	Window(std::string name, int width, int height);
	useconds_t GetSpeed();
	bool isClosed();
	key getLastPressed();
	void poolEvents();
	void clear();
	~Window();
};

Window::Window(std::string name, int width, int height)
{
	this->width = width;
	this->height = height;
	this->name = name;

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


// Grid and stuff
enum Colors
{
	RED = 0, GREEN, BLUE, YELLOW, PINK, PASTELBLUE, WHITEBLUE, GOLD, MEDIUMORCHID, CORNSILK, GRAY42, TURMERIC, TURMERICLIGHT
};

struct Color
{
	int R; // Red
	int G; // Green
	int B; // Blue
	int A; // Alpha-channel

	Color(int R, int G, int B, int A);
	Color operator=(const Color &color);
	Color();
};

struct _2DPoint
{
	int x;
	int y;

	_2DPoint(int x, int y);
	_2DPoint();
};

class Rectangle
{
	int width, height;
	_2DPoint pos;
	Color color;
	Window *window;
	SDL_Rect sdl_rect;
public:
	Rectangle(Window *window, const _2DPoint &pos, int width, int height, const Color &color);
	Rectangle();
	void SetRectangle(Window *window, const _2DPoint &pos, int width, int height, const Color &color);
	void SetColor(Colors newColor);
	void draw();
};

class Grid
{
    uint8_t     *map = nullptr;
	Rectangle   **grid = nullptr;
	int	rows;
	int columns;
	int rect_width;
	int rect_height;
	int stride;
	_2DPoint pos;
	Window *window;

	public:
	Grid(Window *window, const _2DPoint pos, int rows, int columns, int rect_width, int rect_height, int strideBetweenPixels);
	void SetGrid();
    void SetMap(uint8_t* map);
	void Draw();
};

Colors colors[] =
{
	RED, GREEN, BLUE, YELLOW, PINK, PASTELBLUE, WHITEBLUE, GOLD, MEDIUMORCHID, CORNSILK, GRAY42
};

_2DPoint::_2DPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

_2DPoint::_2DPoint()
{
}

Color Color::operator=(const Color &color)
{
	return Color(this->R = color.R, this->G = color.G, this->B = color.B, this->A = color.A);
}

Color::Color()
{
}

Color::Color(int R, int G, int B, int A)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = A;
}

Rectangle::Rectangle(Window *window, const _2DPoint &pos, int width, int height, const Color &color)
{
	SetRectangle(window, pos, width, height, color);
}

void Rectangle::SetRectangle(Window *window, const _2DPoint &pos, int width, int height, const Color &color)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	this->width = width;
	this->height = height;

	this->color = color;
	this->window = window;

	this->sdl_rect.h = this->height;
	this->sdl_rect.w = this->width;
	this->sdl_rect.x = this->pos.x;
	this->sdl_rect.y = this->pos.y;
}

Rectangle::Rectangle()
{
}

void Rectangle::draw()
{
	SDL_SetRenderDrawColor(window->renderer, color.R, color.G, color.B, color.A);
	SDL_RenderFillRect(window->renderer, &sdl_rect);
}

void Rectangle::SetColor(Colors newColor)
{
	switch(newColor)
	{
		case TURMERIC:
			color = Color(115, 44, 70, 180); break;
		case TURMERICLIGHT:
			color = Color(200, 65, 70, 180); break;
		case BLUE:
			color = Color{70, 60, 115, 180}; break;
		case WHITEBLUE:
			color = Color(70, 90, 200, 180); break;
		case GRAY42:
			color = Color(35, 35, 35, 255); break;
		case RED:
			color = Color{255, 0, 0, 255}; break;
		case GREEN:
			color = Color{0, 255, 0, 255}; break;
		case YELLOW:
			color = Color{255, 255, 0, 255}; break;
		case PINK:
			color = Color{255, 0, 255, 255}; break;
		case PASTELBLUE:
			color = Color(153, 153, 255, 255); break;
		case GOLD:
			color = Color(255, 215, 0, 255); break;
		case MEDIUMORCHID:
			color = Color(186, 85, 211, 255); break;
		case CORNSILK:
			color = Color(205, 200, 177, 255); break;
		default:
			break;
	}
}

Grid::Grid(Window *window, const _2DPoint pos, int rows, int columns, int rect_width, int rect_height, int strideBetweenPixels)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;

	this->rows = rows;
	this->columns = columns;

	this->rect_width = rect_width;
	this->rect_height = rect_height;

	this->window = window;

	this->stride = strideBetweenPixels;

	grid = new Rectangle*[rows];
	for (int i = 0; i < rows; ++i)
		grid[i] = new Rectangle[columns];
}

void Grid::SetGrid()
{
	int x = pos.x;
	int y = pos.y;

	for	(int i = 0; i < rows; ++i, y += rect_height + stride)
	{
		x = pos.x;
		for (int j = 0; j < columns; ++j, x += rect_width + stride)
			grid[i][j].SetRectangle(window, _2DPoint{x, y}, rect_width, rect_height, Color{102, 0, 102, 255});
	}
}

void Grid::Draw()
{
	for	(int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->columns; ++j)
        {
            uint8_t currByte = map[(i * this->columns) + j];
			if (currByte == 0)
				this->grid[i][j].SetColor(Colors::GRAY42);
			else if (currByte == 1)
				this->grid[i][j].SetColor(Colors::TURMERIC);
			else
				this->grid[i][j].SetColor(Colors::BLUE);
                
            this->grid[i][j].draw();
        }
	}
}

void Grid::SetMap(uint8_t* map)
{
    this->map = map;
}


// int		main(void)
// {
// 	Window window("Nibbler [SDL2]", WIDTH, HEIGHT);


// 	Grid grid{&window, _2DPoint{0, 0}, rows, columns, square_size, square_size, stride};
// 	grid.SetGrid();

// 	while (!window.isClosed())
// 	{
// 		grid.draw();
// 		window.poolEvents();
// 		window.clear();
// 	}
// 	return (0);
// }

//--------------------------------------------------------


namespace
{
	static ::Window		*window;
	static ::Grid		*grid;
    static uint8_t      *map;

	int squareSide = 30;
	int stride = 3;
}

extern "C"
void    init(uint8_t gridWidth, uint8_t gridHeight)
{
	window = new ::Window("Nibbler [SDL2]", gridWidth * squareSide + stride * gridWidth,
									gridHeight * squareSide + stride * gridHeight);
	grid = new ::Grid(window, _2DPoint{ 0, 0 }, (int)gridHeight, (int)gridWidth, squareSide, squareSide, stride);

    grid->SetGrid();
    grid->SetMap(map);
}

extern "C"
void	destroy()
{
	delete grid;
	delete window;
}

extern "C"
void	draw()
{
    grid->Draw();
    window->poolEvents();
    window->clear();
}

extern "C"
void	setGrid(uint8_t* gridPtr)
{
    map = gridPtr;
}

extern "C"
key		getLastPressed()
{
	return window->getLastPressed();
}
