#include "ClientController.hpp"

ClientController::ClientController(socketPtr sock) :
	sock_(sock)
{
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
	lastPressed_ = Key::RIGHT;

	while (true)
	{
		sendMap_(err);
		if (err)
			break;
		readKey_(err);
		if (err)
			break;
	}
}

void ClientController::sendMap_(boost::system::error_code& err)
{
	static std::vector<uint8_t> mapBuff;
	static std::string ackBuff;

	if (mapBuff.empty())
		mapBuff.resize(gameBoard_->getHeight() * gameBoard_->getWidth());
	if (ackBuff.empty())
		ackBuff.resize(2);
	auto mapIt = mapBuff.begin();
	for (size_t i = 0; i < gameBoard_->getHeight(); ++i)
		for (size_t j = 0; j < gameBoard_->getWidth(); ++j, ++mapIt)
			*mapIt = (*gameBoard_)[{j, i}];
	sock_->write_some(boost::asio::buffer(mapBuff), err);
	if (processErrors(err))
		return;
	sock_->read_some(boost::asio::buffer(ackBuff));
	if (ackBuff != "ok")
		std::cerr << "ackBuff != ok" << std::endl;
	if (processErrors(err))
		return;
}

void ClientController::readKey_(boost::system::error_code& err)
{
	static size_t	lastReadBytes = 0;
	static char		buff;

	lastReadBytes = sock_->read_some(boost::asio::buffer(&buff, sizeof(buff)), err);
	if (processErrors(err))
		return;
	if (lastReadBytes)
	{
		switch(buff)
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

bool ClientController::processErrors(boost::system::error_code &err)
{
	if (err)
	{
		std::cerr << "Couldn't read from client or client closed connection." << std::endl;
		sock_->close();
		return true;
	}
	return false;
}

