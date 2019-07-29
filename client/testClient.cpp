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
	uint8_t buff[buff_size];
	uint32_t offset = 0;
	sock->async_connect(ep, [&buff, &service, &sock, &offset](const boost::system::error_code& ec)
	{
		std::memset(buff, 0, buff_size);
		initscr();
		curs_set(0);
		timeout(5);
		char key[2];
		key[1] = 0;
		key[0] = 'd';
		char map[30 * 30];
		boost::system::error_code err;
		while (true)
		{
			sock->read_some(buffer(map, 30 * 30), err);
			if (err)
			{
				std::cout << "err " << err.message() << std::endl;
				return;
			}
			for (int i = 0; i < 30; ++i)
			{
				for (int j = 0; j < 30; ++j)
				{
					char toPrintBuff[2];
					toPrintBuff[0] = map[(i * 30) + j];
					toPrintBuff[1] = 0;
					if (!toPrintBuff[0])
						mvprintw(i, j, ".\0");
					else if (toPrintBuff[0] == 2)
						mvprintw(i, j, "F\0");
					else
						mvprintw(i, j, "o\0");
				}
			}
			char prevKey = key[0];
			key[0] = getch();
			if (key[0] == -1)
				key[0] = prevKey;
			sock->write_some(buffer(key, 1));
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			clear();
		}
		endwin();
	});
	service.run();
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
