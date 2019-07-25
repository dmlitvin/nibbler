#include "ClientController.hpp"

ClientController::ClientController(socketPtr sock) :
	sock_(sock)
{
	std::thread th{&ClientController::run, this};
	th.detach();
}

void ClientController::setDirectionControl(direction_t& direction) { direction_ = &direction; }

void ClientController::setGameBoard(const GameBoard& gameBoard) { gameBoard_ = &gameBoard; }

void ClientController::updateDirection(cord_t headPosition)
{
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

void ClientController::run()
{
	boost::system::error_code err;
	size_t lastReadBytes = 0;
	const size_t BUFF_SIZE = 1;
	char buff[BUFF_SIZE];
	lastPressed_ = Key::RIGHT;
	while (true)
	{
		lastReadBytes = sock_->read_some(boost::asio::buffer(buff, 1), err);
		if (err)
		{
			std::cerr << "Couldn't read from client or client closed connection." << std::endl;
			sock_->close();
			return;
		}
		if (lastReadBytes)
		{
			switch(buff[0])
			{
				case 'a':
					lastPressed_ = Key::LEFT;
					break;
				case 's':
					lastPressed_ = Key::DOWN;
					break;
				case 'd':
					lastPressed_ = Key::RIGHT;
					break;
				case 'w':
					lastPressed_ = Key::UP;
					break;
				default:
					std::cout << "Unknown key" << std::endl;
			}
		}
	}
}

