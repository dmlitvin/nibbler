#include <iostream>
#include "Snake.hpp"

unsigned    Snake::snakeCount = 0;

entityType  Snake::nextSnakeType() { return static_cast<entityType>(snakeCount + 3); }

Snake::Snake(const GameBoard & gameBoard, IController* controller, cord_t startPosition)
: controller_(controller), gameBoard_(gameBoard)
{
	std::cout << "X == " << (int)startPosition.first << " Y == " << (int)startPosition.second << std::endl;
    int initPosX = startPosition.first,
        initPosY = startPosition.second,
        directionX = direction_.first,
        directionY = direction_.second;

    location_.push_back({initPosX + directionX * 1, initPosY + directionY * 1});
    location_.push_back({initPosX + directionX * 0, initPosY + directionY * 0});
    location_.push_back({initPosX + directionX * -1, initPosY + directionY * -1});
    location_.push_back({initPosX + directionX * -2, initPosY + directionY * -2});

    controller_->setDirectionControl(direction_);
    controller_->setGameBoard(gameBoard_);

    snakeCount++;
}

Snake::~Snake() { snakeCount--; /* delete controller_ ; */ }

unsigned        Snake::getScore()   const { return score_; }
unsigned        Snake::getSpeed()   const { return speed_; }
entityType      Snake::getType()    const { return type_; }
Snake::operator bool()              const { return isAlive; }

const std::vector<cord_t>&  Snake::getLocation() const      { return location_; }

void    Snake::move()
{
    controller_->updateDirection(location_.front());

    const cord_t        currPos = location_.front();
    const direction_t   futurePos = {currPos.first + direction_.first, currPos.second + direction_.second};

    if (futurePos.first >= gameBoard_.getWidth() || futurePos.first < 0
    ||  futurePos.second >= gameBoard_.getHeight() || futurePos.second < 0
    ||  gameBoard_[futurePos] > static_cast<uint8_t>(entityType::food))
        isAlive = false;
    else
    {
        location_.insert(location_.begin(), futurePos);
        if (gameBoard_[futurePos] == static_cast<uint8_t>(entityType::food))
        {
            score_++;
            if (score_ % 3 == 0)
                speed_++;
        }
        else
            location_.pop_back();
    }
}
