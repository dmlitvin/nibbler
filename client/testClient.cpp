#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <string>
#include <memory>
#include <ncurses.h>
#include "DLLHandler.hpp"

using socket_ptr = std::shared_ptr<boost::asio::ip::tcp::socket>;

int		main(int argc, char **argv)
{
	try{
	if (argc != 2)
	{
		std::cerr << "Usage: ./NibblerClient [domen]" << std::endl;
		exit(EXIT_FAILURE);
	}
    static const std::string libNames[] = {"sfml/libsfml", "ncurses/libncurses", "sdl2/libsdl2"};
	boost::system::error_code error;
	boost::asio::io_service service;
	boost::asio::ip::tcp::resolver resolver(service);
	boost::asio::ip::tcp::resolver::query query(argv[1], "4242");

	boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve( query, error);
	if (error)
	{
		std::cerr << "something went wrong.." << std::endl;
		exit(EXIT_FAILURE);
	}
	boost::asio::ip::tcp::endpoint ep = *iter;
	socket_ptr sock(new boost::asio::ip::tcp::socket(service));
	// boost::system::error_code error;
	sock->async_connect(ep, [&sock](const boost::system::error_code& ec)
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
		boost::asio::read(*sock, boost::asio::buffer(mapStats, 4), boost::asio::transfer_exactly(4), err);
		if (err)
		{
			std::cout << "err " << err.message() << std::endl;
			return;
		}

		boost::asio::write(*sock, boost::asio::buffer("ok", 2), boost::asio::transfer_exactly(2), err);
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
			boost::asio::read(*sock, boost::asio::buffer(map, mapWidth * mapHeight), boost::asio::transfer_exactly(mapWidth * mapHeight), err);
			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}

			boost::asio::write(*sock, boost::asio::buffer("ok", 2), boost::asio::transfer_exactly(2), err);
			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}

            static std::map<key, char>  keyChar = {{key::UP, 'w'}, {key::DOWN, 's'}, {key::LEFT, 'a'}, {key::RIGHT, 'd'}};
			static std::map<char, key>	charKey = {{'w', key::UP}, {'s', key::DOWN}, {'a', key::LEFT}, {'d', key::RIGHT}};

			key lastKey = graphicHandler.getLastPressed();
            graphicHandler.draw();

            if (lastKey < key::NB1)
                keyBuff[0] = keyChar[lastKey];
            else if (lastKey >= key::NB1 && lastKey <= key::NB3)
			{
				graphicHandler.changeLibrary("graphicLibraries/" + libNames[lastKey - 4] + "Nibbler.dylib", charKey[keyBuff[0]]);
				lastKey = charKey[keyBuff[0]];
			}
			else
				std::cout << lastKey << std::endl;

			boost::asio::write(*sock, boost::asio::buffer(keyBuff, 1), boost::asio::transfer_exactly(1), err);

			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}
			static std::string buff;
			if (buff.empty())
				buff.resize(2);

			boost::asio::read(*sock, boost::asio::buffer(buff, 2), boost::asio::transfer_exactly(2), err);

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
	}
	catch(...)
	{
		std::cerr << "something went wrong" << std::endl;
	}
	return 0;
}
