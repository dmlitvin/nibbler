#pragma once

# include <iostream>
# include <boost/asio.hpp>
# include <thread>
# include <memory>
# include <mutex>
# include <map>

class Server
{
public:
	using socketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;
	using clientId = uint8_t;	// less than 256 clients

	Server();

	void acceptClients(uint8_t count);

private:

	void clientConnected_(socketPtr sock, clientId id, const boost::system::error_code& err);

	constexpr static uint16_t		SERVER_PORT = 4242;
	constexpr static char			MSG_END = '\n';


	boost::asio::io_service			service_;
	boost::asio::ip::tcp::endpoint	endPoint_;
	boost::asio::ip::tcp::acceptor	acceptor_;

	clientId						nextClientId_ = 0;
	std::map<clientId, socketPtr>	clients_;
	std::mutex						clientsProtect_;
};
