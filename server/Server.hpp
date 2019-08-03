#pragma once

# include <iostream>
# include <boost/asio.hpp>
# include <thread>
# include <memory>
# include <mutex>
# include <thread>
# include <map>

# include "Snake.hpp"
# include "ClientController.hpp"
# include "ComputerController.hpp"

class Server
{
public:
	using socketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;
	using clientId = uint16_t;
	using snakePtr = Snake*;
	using boardPtr = std::shared_ptr<GameBoard>;
	using ioServicePtr = std::shared_ptr<boost::asio::io_service>;
	using endPointPtr = std::shared_ptr<boost::asio::ip::tcp::endpoint>;
	using acceptorPtr = std::shared_ptr<boost::asio::ip::tcp::acceptor>;

	explicit Server(char *argv[]);
	Server(const Server &rhs) = delete;
	Server &operator=(const Server &rhs) = delete;
	~Server() = default;

	void acceptClients(char *argv[]);

	void startGame();

private:

	uint32_t fruitGenRate = 0;

	void clientConnected_(socketPtr sock, clientId id, const boost::system::error_code& err);
	uint16_t getNumberFromArg_(char* arg);

	constexpr static uint16_t		SERVER_PORT = 4242;

	ioServicePtr					service_ = nullptr;
	endPointPtr						endPoint_ = nullptr;
	acceptorPtr						acceptor_ = nullptr;

	clientId						nextClientId_ = 1;
	clientId						bots_ = 0;
	std::mutex						clientsProtect_;

	std::vector<IController*> controllers_;

	bool gameOver_ = false;
	std::vector<snakePtr> players_;
	boardPtr board_ = nullptr;
};
