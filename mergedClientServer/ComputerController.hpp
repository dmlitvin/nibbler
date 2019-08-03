#pragma once

#include "IController.hpp"
#include <map>
#include <list>

struct ComputerController : IController
{

    struct room_t
    {
        cord_t              parentCord = {-1, -1};
        uint32_t            distance = ~0u;
        std::list<cord_t>   linkList;
    };

    ComputerController() = default;

    ComputerController(const ComputerController &)              = delete;
    ComputerController& operator=(const ComputerController &)   = delete;

    void    updateDirection(cord_t)             override;
    void    setGameBoard(const GameBoard &)     override;
    void    setDirectionControl(direction_t &)  override;

    ~ComputerController() = default;

private:

    GameBoard const     *gameBoard_ = nullptr;
    direction_t         *direction_ = nullptr;

};
