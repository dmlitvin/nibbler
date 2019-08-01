#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <string>
#include <memory>
#include <ncurses.h>
#include "DLLHandler.hpp"

//using namespace std;
const int buff_size = 1000000;
using namespace boost::asio;

using socket_ptr = std::shared_ptr<ip::tcp::socket>;

int		main(int argc, char **argv)
{
	io_service service;
	ip::tcp::resolver resolver(service);
	ip::tcp::resolver::query query(argv[1], "4242");
	ip::tcp::resolver::iterator iter = resolver.resolve( query);
	ip::tcp::endpoint ep = *iter;
	socket_ptr sock(new ip::tcp::socket(service));
	boost::system::error_code error;
	uint32_t offset = 0;
	sock->async_connect(ep, [&service, &sock, &offset](const boost::system::error_code& ec)
	{
		if (ec)
		{
			std::cerr << "Error: Couldn't connect to server" << std::endl;
			return;
		}
		char keyBuff[2];
		keyBuff[1] = 0;
		keyBuff[0] = 'd';

		boost::system::error_code err;
		uint16_t mapStats[2];
		boost::asio::read(*sock, buffer(mapStats, 4), boost::asio::transfer_exactly(4), err);
		if (err)
		{
			std::cout << "err " << err.message() << std::endl;
			return;
		}

//	sock->read_some(buffer(mapStats, sizeof(mapStats)));

//		sock->write_some(buffer("ok", 2));
		boost::asio::write(*sock, buffer("ok", 2), boost::asio::transfer_exactly(2), err);
		if (err)
		{
			std::cout << "err " << err.message() << std::endl;
			return;
		}

		uint16_t mapHeight = mapStats[0], mapWidth = mapStats[1];

		uint8_t * map = new uint8_t[mapHeight * mapWidth];

		DLLHandler  graphicHandler(std::string("graphicLibraries/sfmldll/sfml") + "NibblerLib.dylib", mapWidth, mapHeight);
		graphicHandler.init();
		graphicHandler.setGrid(map);

		while (true)
		{
//			sock->read_some(buffer(map, mapWidth * mapHeight), err);
			boost::asio::read(*sock, buffer(map, mapWidth * mapHeight), boost::asio::transfer_exactly(mapWidth * mapHeight), err);
			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}

			boost::asio::write(*sock, buffer("ok", 2), boost::asio::transfer_exactly(2), err);
			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}

            static std::map<key, char>  keyChar = {{key::UP, 'w'}, {key::DOWN, 's'}, {key::LEFT, 'a'}, {key::RIGHT, 'd'}};

            graphicHandler.draw();
            keyBuff[0] = keyChar[graphicHandler.getLastPressed()];

//			sock->write_some(buffer("ok", 2));
//			char prevKey = key[0];

			boost::asio::write(*sock, buffer(keyBuff, 1), boost::asio::transfer_exactly(1), err);
//			sock->write_some(buffer(key, 1));

			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}
			static std::string buff;
			if (buff.empty())
				buff.resize(2);

			boost::asio::read(*sock, buffer(buff, 2), boost::asio::transfer_exactly(2), err);
//			sock->read_some(buffer(buff, 2));

			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}
			if (buff != "ok")
			{
				std::cerr << "ackBuff != ok " << std::endl;
				std::cerr << static_cast<int>(buff[0]) << " " << static_cast<int>(buff[1]) << std::endl;
				return;
			}
//			std::this_thread::sleep_for(std::chrono::milliseconds(70));

        }
		endwin();
	});
	service.run();
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
