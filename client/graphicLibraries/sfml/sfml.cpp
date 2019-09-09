#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "../../key.h"

namespace
{
    static sf::RenderWindow *window;


    static uint8_t *gridPtr;
    static uint8_t gridWidth;
    static uint8_t gridHeight;

    static const int squareSide = 30;

    static key lastPressed = key::RIGHT;

    static const sf::Color colors[] = {	sf::Color::Black,
										sf::Color::White,
										sf::Color::Green,
										sf::Color::Red,
										sf::Color::Yellow,
										sf::Color::Magenta,
										sf::Color::Cyan	};
}

extern "C"
void    init(uint8_t gridWidth, uint8_t gridHeight, key initKey)
{
    ::gridWidth = gridWidth;
    ::gridHeight = gridHeight;
	::lastPressed = initKey;

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
	sf::Event event;

	while (window->pollEvent(event))
		if (event.type == sf::Event::EventType::Closed)
			exit(EXIT_SUCCESS);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		exit(EXIT_SUCCESS);

	if (window->isOpen())
	{
		window->clear();

		for (size_t y = 0; y < gridHeight; y++)
			for (size_t x = 0; x < gridWidth; x++)
			{
				sf::RectangleShape rect(
					sf::Vector2f(::squareSide, ::squareSide));
				rect.setPosition(
					sf::Vector2f(::squareSide * x, ::squareSide * y));
				uint8_t blockId = gridPtr[y * gridWidth + x];
				if (blockId < 7)
					rect.setFillColor(colors[blockId]);
				else
					rect.setFillColor(sf::Color::Blue);
				window->draw(rect);
			}

		std::map<sf::Keyboard::Key, key>	keyArray = {{sf::Keyboard::A, key::LEFT},
														{sf::Keyboard::D, key::RIGHT},
														{sf::Keyboard::S, key::DOWN},
														{sf::Keyboard::W, key::UP},
														{sf::Keyboard::Num1, key::NB1},
														{sf::Keyboard::Num2, key::NB2},
														{sf::Keyboard::Num3, key::NB3}};

		for (const auto & keyPair : keyArray)
			if (sf::Keyboard::isKeyPressed(keyPair.first))
				lastPressed = keyPair.second;

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
