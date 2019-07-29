#include "Server.hpp"

void    deleteSnakeFromMap(const std::vector<cord_t> & snakeLocation, GameBoard & board)
{
	for (const auto & snakeCord : snakeLocation)
		board[snakeCord] = static_cast<uint8_t>(entityType::empty);
}

void    putSnakeToMap(const Snake & snake, GameBoard & board)
{
	for (const auto snakeCord : snake.getLocation())
		board[snakeCord] = static_cast<uint8_t>(snake.getType());
}

Server::Server() :
	endPoint_(boost::asio::ip::tcp::v4(), SERVER_PORT),
	acceptor_(service_, endPoint_),
	board_(30, 30)
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
	return clientsCount;
}

void Server::acceptClients(uint32_t argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./server [players count]" << std::endl;
		return;
	}

	clientId clientsCount = getClientsCountFromArg_(argv[0]);
	bots_ = getClientsCountFromArg_(argv[1]);

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
//	std::cout << "Accepted new participant with id: " << static_cast<uint32_t>(id) << std::endl;
//	std::string echoMsg = "You connected to server, your ID is " + std::to_string(id) + Server::MSG_END;
//	sock->write_some(boost::asio::buffer(echoMsg));

	// TODO: sending map size
//	std::string mapSizeMsg(std::to_string(board_.getWidth() + ' ' + board_.getHeight()));
//	sock->write_some(mapSizeMsg);

	IController* controller = new ClientController(sock);
	// TODO: make_unique doesnt work
	players_.push_back(std::shared_ptr<Snake>(new Snake(board_, controller, {id * 10, id * 10})));
	controllers_.push_back(controller);
}

void Server::startGame()
{
	for (size_t i = 0; i < players_.size(); ++i)
	{
		std::thread th{&ClientController::run, reinterpret_cast<ClientController*>(players_[i]->getController())};
		th.detach();
	}
	for (clientId i = 0; i < bots_; ++i)
	{
		IController* botController = new ComputerController();
		players_.push_back(snakePtr(new Snake(board_, botController, {nextClientId_ * 4, 8})));
		controllers_.push_back(botController);
		++nextClientId_;
	}
	int i = 0;

	fruitGenRate = (1 / static_cast<double>(players_.size())) * 100;

	while (!gameOver_)
	{
		auto it = players_.begin();
		while (it != players_.end())
		{
			auto& snake = **it;
			auto  toDelete = snake.getLocation();
			snake.move();
			deleteSnakeFromMap(toDelete, board_);
			putSnakeToMap(snake, board_);

			if (**it)
				it++;
			else
			{
				deleteSnakeFromMap(it->get()->getLocation(), board_);
				it = players_.erase(it);
			}
		}
//		std::cout << board_ << std::endl;
		if (!(i % fruitGenRate))
			board_[rand() % board_.getHeight()][rand() % board_.getWidth()] = static_cast<uint8_t>(entityType::food);
		++i;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
