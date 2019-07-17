#include <iostream>
#include "Snake.hpp"
#include "ComputerController.hpp"

std::ostream&   operator<<(std::ostream& stream, const GameBoard& board)
{
    std::map<uint8_t, char> map = {{0, '.'}, {1, 'B'}, {2, 'F'}, {3, 'S'}, {4, 's'}, {5, 'Z'}, {6, 'z'}};

    for (size_t y = 0; y < board.getHeight(); y++)
    {
        for (size_t x = 0; x < board.getWidth(); x++)
            stream << map[board[y][x]];
        stream << std::endl;
    }

    return stream << std::endl;
}

void    deleteSnakeFromMap(std::vector<cord_t> snakeLocation, GameBoard & board)
{
    for (const auto & snakeCord : snakeLocation)
        board[snakeCord] = static_cast<uint8_t>(entityType::empty);
}

void    putSnakeToMap(const Snake & snake, GameBoard & board)
{
    for (const auto snakeCord : snake.getLocation())
        board[snakeCord] = static_cast<uint8_t>(snake.getType());
}

int     main()
{
    GameBoard   gameBoard(30, 30);

    std::vector<std::unique_ptr<Snake>> snakes;
    snakes.push_back(std::unique_ptr<Snake>(new Snake(gameBoard, new ComputerController, {2, 2})));
    snakes.push_back(std::unique_ptr<Snake>(new Snake(gameBoard, new ComputerController, {5, 5})));
    snakes.push_back(std::unique_ptr<Snake>(new Snake(gameBoard, new ComputerController, {8, 8})));
    snakes.push_back(std::unique_ptr<Snake>(new Snake(gameBoard, new ComputerController, {15, 15})));

    for (const auto & snake : snakes)
        putSnakeToMap(*snake, gameBoard);

    {
        size_t i = 35;

        while (i--)
        {
            auto it = snakes.begin();

            while (it != snakes.end())
            {
                auto& snake = *it->get();
                auto  toDelete = snake.getLocation();
                snake.move();
                deleteSnakeFromMap(toDelete, gameBoard);
                putSnakeToMap(snake, gameBoard);

                if (**it)
                    it++;
                else
                {
                    deleteSnakeFromMap(it->get()->getLocation(), gameBoard);
                    it = snakes.erase(it);
                }
            }

            std::cout << gameBoard;
        }

    }

    return 0;
}
