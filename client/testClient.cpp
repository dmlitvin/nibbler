#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <string>
#include <memory>
#include <ncurses.h>
#include <ncurses.h>

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
		initscr();
		curs_set(0);
		timeout(5);
		char key[2];
		key[1] = 0;
		key[0] = 'd';

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

		char* map = new char[mapHeight * mapWidth];
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
//			sock->write_some(buffer("ok", 2));
			for (int i = 0; i < mapHeight; ++i)
			{
				for (int j = 0; j < mapWidth; ++j)
				{
					char toPrintBuff[2];
					toPrintBuff[0] = map[(i * mapWidth) + j];
					toPrintBuff[1] = 0;
					if (!toPrintBuff[0])
						mvprintw(i, j, ".\0");
					else if (toPrintBuff[0] == 1)
						mvprintw(i, j, "F\0");
					else
						mvprintw(i, j, "o\0");
				}
			}
//			char prevKey = key[0];
			key[0] = getch();
			if (key[0] == -1)
				key[0] = 'c';
			boost::asio::write(*sock, buffer(key, 1), boost::asio::transfer_exactly(1), err);
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
			erase();
		}
		endwin();
	});
	service.run();
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
