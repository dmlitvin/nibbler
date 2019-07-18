#include "Server.hpp"

Server::Server() :
	endPoint_(boost::asio::ip::tcp::v4(), SERVER_PORT),
	acceptor_(service_, endPoint_)
{ }

void Server::acceptClients(uint8_t count)
{
	auto clientConnected = std::mem_fn(&Server::clientConnected_);

	for (uint8_t i = 0; i < count; ++i)
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
	std::cout << sock->write_some(boost::asio::buffer(echoMsg)) << std::endl;
	clients_.insert({ id, sock });
}
