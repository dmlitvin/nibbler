#pragma once

#include "GameBoard.hpp"
#include <utility>

using direction_t = std::pair<int, int>;

struct IController
{

    virtual void    setDirectionControl(direction_t &) = 0;
    virtual void    setGameBoard(const GameBoard &) = 0;
    virtual void    updateDirection(cord_t) = 0;

    virtual ~IController() {}

};
