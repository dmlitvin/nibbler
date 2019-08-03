#include "Grid.hpp"

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
			else if (currByte == 3)
				this->grid[i][j].SetColor(Colors::BLUE);
			else if (currByte == 4)
				this->grid[i][j].SetColor(Colors::GOLD);
			else if (currByte == 5)
				this->grid[i][j].SetColor(Colors::GREEN);
			else if (currByte == 6)
				this->grid[i][j].SetColor(Colors::WHITEBLUE);
            else
				this->grid[i][j].SetColor(Colors::CORNSILK);
            this->grid[i][j].draw();
        }
	}
}

void Grid::SetMap(uint8_t* map)
{
    this->map = map;
}
Grid::~Grid()
{
	for (int i = 0; i < rows; ++i)
		delete grid[i];
	delete grid;
}