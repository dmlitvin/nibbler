#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../key.h"

namespace
{
    static sf::RenderWindow *window;

    static uint8_t *gridPtr;
    static uint8_t gridWidth;
    static uint8_t gridHeight;

    static const int squareSide = 30;

    static key lastPressed = key::RIGHT;
}

extern "C"
void    init(uint8_t gridWidth, uint8_t gridHeight)
{
    ::gridWidth = gridWidth;
    ::gridHeight = gridHeight;

    window = new sf::RenderWindow(sf::VideoMode(squareSide * gridWidth, squareSide * gridHeight), "sfml Nibbler");
}

extern "C"
void    destroy()
{
    window->close();
    delete window;
}

extern "C"
void    draw()
{
    sf::Event   event;

    while (window->pollEvent(event))
        if (event.type == sf::Event::EventType::Closed)
            exit(EXIT_SUCCESS);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        exit(EXIT_SUCCESS);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window->close();

    if (window->isOpen())
    {
        window->clear();

        for (size_t y = 0; y < gridHeight; y++)
            for (size_t x = 0; x < gridWidth; x++)
            {
                sf::RectangleShape  rect(sf::Vector2f(::squareSide, ::squareSide));
                rect.setPosition(sf::Vector2f(::squareSide * x, ::squareSide * y));
                if (!::gridPtr[y * gridWidth + x])
                    rect.setFillColor(sf::Color::Black);
                else if (gridPtr[y * gridWidth + x] == 1)
                    rect.setFillColor(sf::Color::Green);
                else
                    rect.setFillColor(sf::Color::Red);
                window->draw(rect);
            }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            lastPressed = key::LEFT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            lastPressed = key::RIGHT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            lastPressed = key::DOWN;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            lastPressed = key::UP;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            lastPressed = key::NB1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            lastPressed = key::NB2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            lastPressed = key::NB3;

        window->display();
    }
}

extern "C"
void    setGrid(uint8_t *gridPtr)
{
    ::gridPtr = gridPtr;
}

extern "C"
key     getLastPressed()
{
    return lastPressed;
}
