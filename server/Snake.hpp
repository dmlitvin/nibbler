#pragma once

#include "GameBoard.hpp"
#include "IController.hpp"

struct Snake
{
    Snake(const GameBoard &, IController*, cord_t);

    unsigned        getScore()  const;
    unsigned        getSpeed()  const;
    entityType      getType()   const;
    operator        bool()      const;

    virtual void    move();

    const std::vector<cord_t>&  getLocation() const;

    Snake& operator=(const Snake&)  = delete;
    Snake(Snake const&)             = delete;
    Snake()                         = delete;

    ~Snake();

    static unsigned snakeCount;

private:

    static entityType   nextSnakeType();

    bool                isAlive = true;
    unsigned            score_ = 0, speed_ = 1;
    entityType          type_ = nextSnakeType();
    IController         *controller_;
    direction_t         direction_ = {0, 1};
    const GameBoard&    gameBoard_;
    std::vector<cord_t> location_;

};
