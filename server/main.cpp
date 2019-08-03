#include "Server.hpp"

int main(int argc, char *argv[])
{
	try{
	if (argc != 5)
	{
		std::cerr << "Usage: ./server [map_height] [map_width] [players count] [bots count]" << std::endl;
		return 1;
	}

	Server server{argv + 1};
	server.acceptClients(argv + 3);
	server.startGame();
	}
	catch(...)
	{
		std::cerr << "something went wrong" << std::endl;
	}
	return 0;
}
