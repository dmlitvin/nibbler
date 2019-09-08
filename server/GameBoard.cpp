#include "GameBoard.hpp"

GameBoard::GameBoard(int width, int height) : width_(width), height_(height),
matrix(height_, std::vector<uint8_t>(width_, static_cast<int>(entityType::empty))) {}

int GameBoard::getWidth()   const    { return width_; }
int GameBoard::getHeight()  const    { return height_; }

std::vector<uint8_t>&       GameBoard::operator[](size_t index)         { return matrix[index]; }
const std::vector<uint8_t>& GameBoard::operator[](size_t index) const   { return matrix[index]; }

uint8_t&        GameBoard::operator[](cord_t index)         { return matrix[index.second][index.first]; }
const uint8_t&  GameBoard::operator[](cord_t index) const   { return matrix[index.second][index.first]; }

std::ostream&   operator<<(std::ostream& stream, const GameBoard& board)
{
	std::map<uint8_t, char> map = {{0, '.'}, {1, 'F'}, {2, 'B'}, {3, 'S'}, {4, 's'}, {5, 'Z'}, {6, 'z'}};

	for (int y = 0; y < board.getHeight(); y++)
	{
		for (int x = 0; x < board.getWidth(); x++)
			stream << map[board[y][x]];
		stream << std::endl;
	}

	return stream << std::endl;
}

cord_t make_cord_t(uint8_t first, uint8_t second) noexcept
{
	return std::make_pair(first, second);
}
