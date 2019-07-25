#include "ClientController.hpp"

ClientController::ClientController(socketPtr sock) :
	sock_(sock)
{
}

void ClientController::setDirectionControl(direction_t& direction) { direction_ = &direction; }

void ClientController::setGameBoard(const GameBoard& gameBoard) { gameBoard_ = &gameBoard; }

void ClientController::updateDirection(cord_t headPosition)
{
	*direction_ = {1, 0};
}

