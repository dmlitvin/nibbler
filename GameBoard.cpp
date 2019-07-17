#include "GameBoard.hpp"

GameBoard::GameBoard(int width, int height) : width_(width), height_(height),
matrix(height_, std::vector<uint8_t>(width_, static_cast<int>(entityType::empty))) {}

int GameBoard::getWidth()   const    { return width_; }
int GameBoard::getHeight()  const    { return height_; }

std::vector<uint8_t>&       GameBoard::operator[](size_t index)         { return matrix[index]; }
const std::vector<uint8_t>& GameBoard::operator[](size_t index) const   { return matrix[index]; }

uint8_t&        GameBoard::operator[](cord_t index)         { return matrix[index.second][index.first]; }
const uint8_t&  GameBoard::operator[](cord_t index) const   { return matrix[index.second][index.first]; }
