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
    static const std::string libNames[] = {"sfmldll/sfml", "ncurses/libncurses", "sdl2/sdl"};
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

		boost::asio::write(*sock, buffer("ok", 2), boost::asio::transfer_exactly(2), err);
		if (err)
		{
			std::cout << "err " << err.message() << std::endl;
			return;
		}

		uint16_t mapHeight = mapStats[0], mapWidth = mapStats[1];

		uint8_t * map = new uint8_t[mapHeight * mapWidth];

		DLLHandler  graphicHandler("graphicLibraries/" + libNames[0] + "Nibbler.dylib", map, mapWidth, mapHeight);
		graphicHandler.setGrid(map);

		while (true)
		{
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

			key lastKey = graphicHandler.getLastPressed();
            graphicHandler.draw();
            if (lastKey < key::NB1)
                keyBuff[0] = keyChar[lastKey];
            else if (lastKey >= key::NB1 && lastKey <= key::NB3)
			{
				graphicHandler.changeLibrary(
					"graphicLibraries/" + libNames[lastKey - 4] +
						"Nibbler.dylib");
			}
			else
				std::cout << lastKey << std::endl;

			boost::asio::write(*sock, buffer(keyBuff, 1), boost::asio::transfer_exactly(1), err);

			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}
			static std::string buff;
			if (buff.empty())
				buff.resize(2);

			boost::asio::read(*sock, buffer(buff, 2), boost::asio::transfer_exactly(2), err);

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
        }
		endwin();
	});
	service.run();
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
