#include "ComputerController.hpp"

void    ComputerController::setGameBoard(const GameBoard & gameBoard)   { gameBoard_ = &gameBoard; }
void    ComputerController::setDirectionControl(direction_t& direction) { direction_ = &direction; }

static std::list<cord_t>  getLinks(cord_t point, const GameBoard& gameBoard)
{
    int x = point.first, y = point.second, foodId = static_cast<uint8_t>(entityType::food);
    std::list<cord_t>   linkList;

    if (x > 0 && gameBoard[y][x - 1] <= foodId)
        linkList.push_back({x - 1, y});
    if (x < gameBoard.getWidth() - 1 && gameBoard[y][x + 1] <= foodId)
        linkList.push_back({x + 1, y});
    if (y > 0 && gameBoard[y - 1][x] <= foodId)
        linkList.push_back({x, y - 1});
    if (y < gameBoard.getHeight() - 1 && gameBoard[y + 1][x] <= foodId)
        linkList.push_back({x, y + 1});
    
    return linkList;
}

static std::map<cord_t, ComputerController::room_t> graphInit(const GameBoard &gameBoard)
{
    std::map<cord_t, ComputerController::room_t>   returnMap;

    for (int y = 0; y < gameBoard.getHeight(); y++)
        for (int x = 0; x < gameBoard.getWidth(); x++)
            returnMap[{x, y}] = {{0, 0}, ~0u, getLinks({x, y}, gameBoard)};

    return returnMap;
}

void    ComputerController::updateDirection(cord_t headPosition)
{
    const uint8_t   foodId = static_cast<uint8_t>(entityType::food);
    bool            foodReached = false;
    cord_t          foodLocation = {-1, -1};

    std::map<cord_t, ComputerController::room_t>    graph = graphInit(*gameBoard_);

    std::list<cord_t>           birnedCords;
    std::list<cord_t>           aimedCords;

    graph[headPosition].distance = 0;
    birnedCords.push_back(headPosition);

    uint32_t distance = 1;
    while (foodReached == false && !birnedCords.empty())
    {
        for (const auto & cord : birnedCords)
        {
            for (const auto & link : graph[cord].linkList)
            {
                if (graph[link].distance > distance)
                {
                    graph[link].parentCord = cord;
                    graph[link].distance = distance;
                    aimedCords.push_back(link);
                    if (gameBoard_->operator[](link.second)[link.first] == foodId)
                    {
                        foodReached = true;
                        foodLocation = link;
                    }
                }
            }
        }
        birnedCords = std::move(aimedCords);
        distance++;
    }

    if (foodLocation != cord_t(-1, -1))
    {
        cord_t  tmp = foodLocation;
        while (graph[tmp].parentCord != headPosition)
            tmp = graph[tmp].parentCord;
        *direction_ = {tmp.first - headPosition.first, tmp.second - headPosition.second};
    }
    else
    {
        cord_t  tmp = graph[headPosition].linkList.back();
        *direction_ = {tmp.first - headPosition.first, tmp.second - headPosition.second};        
    }
}
