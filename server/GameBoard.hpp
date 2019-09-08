#pragma once

#include <vector>
#include <map>
#include <iostream>
enum class entityType
{
    empty, food, block
};

using cord_t = std::pair<uint8_t, uint8_t>;

cord_t make_cord_t(uint8_t first, uint8_t second);

struct GameBoard
{

    using matrix_t =    std::vector<std::vector<uint8_t>>;

    GameBoard(int, int);

    int getWidth()  const;
    int getHeight() const;

    GameBoard()                             = delete;
    GameBoard& operator=(const GameBoard&)  = delete;
    GameBoard(const GameBoard&)             = delete;

    std::vector<uint8_t>&       operator[](size_t);
    const std::vector<uint8_t>& operator[](size_t) const;

    uint8_t&        operator[](cord_t);
    const uint8_t&  operator[](cord_t) const;

    ~GameBoard() = default;

private:

    int         width_, height_;
    matrix_t    matrix;

};

std::ostream&   operator<<(std::ostream& stream, const GameBoard& board);