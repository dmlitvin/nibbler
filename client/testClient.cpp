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

void on_read(io_service& service, socket_ptr sock, uint8_t* buff, uint32_t& offset, const boost::system::error_code& ec, size_t bytesRead)
{
	if (ec)
	{
		std::cout << ec.message() << std::endl;
		return;
	}
	if (std::find(buff + offset, buff + offset + bytesRead, '\n') < buff + offset + bytesRead)
	{
		return;
	}
//	offset += bytesRead;
//	sock->async_read_some(buffer(buff + offset, buff_size - offset - 1), std::bind(on_read, std::ref(service), sock, buff, std::ref(offset), std::placeholders::_1, std::placeholders::_2));
};

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
		sock->async_read_some(buffer(buff), std::bind(on_read, std::ref(service), sock, buff, std::ref(offset), std::placeholders::_1, std::placeholders::_2));
		initscr();

		curs_set(0);
		timeout(5);
		char key[2];
		key[1] = 0;
		key[0] = -1;
		while (true)
		{
			key[0] = getch();
			if (key[0] != -1)
			{
				sock->write_some(buffer(key, 1));
				clear();
				mvprintw(0, 0, key);
			}
		}
		endwin();
	});
	service.run();
	std::cout << buff << std::endl;
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
