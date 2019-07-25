#include "ClientController.hpp"

ClientController::ClientController(socketPtr sock) :
	sock_(sock)
{
}

void ClientController::setDirectionControl(direction_t& direction) { direction_ = &direction; }

void ClientController::setGameBoard(const GameBoard& gameBoard) { gameBoard_ = &gameBoard; }

void ClientController::updateDirection(cord_t headPosition)
{
	lastPressed_ = static_cast<Key>(rand() % 4);
	Key lastPressed = lastPressed_;

	static const std::map<Key, direction_t>	keyDirection =
		{
			{Key::LEFT,	{-1, 0}},
			{Key::RIGHT,{1, 0}},
			{Key::UP,	{0, -1}},
			{Key::DOWN,	{0, 1}}
		};
	*direction_ = keyDirection.at(lastPressed);

}

