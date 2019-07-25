#include "Server.hpp"

Server::Server() :
	endPoint_(boost::asio::ip::tcp::v4(), SERVER_PORT),
	acceptor_(service_, endPoint_)
{ }

/*
 * returns 0 if invalid value in arg
 * in other cases returns numerical value from arg
 */

Server::clientId Server::getClientsCountFromArg_(char* arg)
{
	clientId clientsCount = 0;
	std::stringstream ss{arg};
	ss >> clientsCount;
	if (clientsCount == std::numeric_limits<decltype(clientsCount)>::max())
	{
		std::cerr << "Number of clients is too big" << std::endl;
		return 0;
	}
	else if (clientsCount == std::numeric_limits<decltype(clientsCount)>::min())
	{
		std::cerr << "Number of clients is too small" << std::endl;
		return 0;
	}
	return clientsCount;
}

void Server::acceptClients(uint32_t argc, char *argv[])
{
	if (argc != 1)
	{
		std::cerr << "Usage: ./server [players count]" << std::endl;
		return;
	}

	clientId clientsCount = getClientsCountFromArg_(argv[0]);

	auto clientConnected = std::mem_fn(&Server::clientConnected_);
	for (clientId i = 0; i < clientsCount; ++i)
	{
		socketPtr newClientSock = std::make_shared<boost::asio::ip::tcp::socket>(service_);
		clientId newClientId = nextClientId_++;
		acceptor_.async_accept(*newClientSock,
			std::bind(clientConnected, this, newClientSock, newClientId, std::placeholders::_1)); 
	}
	service_.run();
}

void Server::clientConnected_(socketPtr sock, clientId id, const boost::system::error_code& err)
{
	if (err)
	{
		std::cerr << "Error happened on acceptClients()" << std::endl;
		std::cerr << err.message() << std::endl;
		return;
	}
	std::lock_guard<std::mutex> dataLock(clientsProtect_);
	std::cout << "Accepted new participant with id: " << static_cast<uint32_t>(id) << std::endl;
	std::string echoMsg = "You connected to server, your ID is " + std::to_string(id) + Server::MSG_END;
	sock->write_some(boost::asio::buffer(echoMsg));
	clients_.insert({ id, sock });
}


