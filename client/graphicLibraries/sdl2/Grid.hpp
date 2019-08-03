#include "Window.hpp"

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

	Color();
    Color(const Color&);
	Color(int R, int G, int B, int A);
	Color operator=(const Color &color);
	~Color() = default;
};

struct _2DPoint
{
	int x;
	int y;

	_2DPoint(int x, int y);
	_2DPoint();
    _2DPoint(const _2DPoint&) = default;
    _2DPoint& operator=(const _2DPoint&) = delete;
	~_2DPoint() = default;
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

    Rectangle(const Rectangle&) = delete;
    Rectangle& operator=(const Rectangle&) = delete;
	~Rectangle() = default;

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

    Grid() = delete;
    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;
	~Grid();
	Grid(Window *window, const _2DPoint pos, int rows, int columns, int rect_width, int rect_height, int strideBetweenPixels);
	void SetGrid();
    void SetMap(uint8_t* map);
	void Draw();
};
