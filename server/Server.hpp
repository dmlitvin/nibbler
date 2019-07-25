#pragma once

# include <iostream>
# include <boost/asio.hpp>
# include <thread>
# include <memory>
# include <mutex>
# include <map>

# include "Snake.hpp"
# include "ClientController.hpp"
# include "ComputerController.hpp"

class Server
{
public:
	using socketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;
	using clientId = uint16_t;
//	using clientSet = std::map<clientId, socketPtr>;
	using snakePtr = std::shared_ptr<Snake>;

	Server();
	Server(const Server &rhs) = delete;
	Server &operator=(const Server &rhs) = delete;
	~Server() = default;

	void acceptClients(uint32_t argc, char *argv[]);

	void startGame();

private:

	void clientConnected_(socketPtr sock, clientId id, const boost::system::error_code& err);
	clientId getClientsCountFromArg_(char* arg);

	constexpr static uint16_t		SERVER_PORT = 4242;
	constexpr static char			MSG_END = '\n';

	boost::asio::io_service			service_;
	boost::asio::ip::tcp::endpoint	endPoint_;
	boost::asio::ip::tcp::acceptor	acceptor_;

	clientId						nextClientId_ = 1;
	clientId						bots_ = 0;
//	clientSet						clients_;
	std::mutex						clientsProtect_;

	std::vector<IController*> controllers_;

	bool gameOver_ = false;
	std::vector<snakePtr> players_;
	GameBoard board_;
};
