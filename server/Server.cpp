#include "Server.hpp"

std::mutex boardLock;

auto checkNum = [](char *str){
	for (int i = 0; str[i]; ++i)
	{
		if (!isnumber(str[i]))
		{
			std::cerr << "Argument has to be only number" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
};

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

Server::Server(char *argv[])
{
	service_ = std::make_shared<boost::asio::io_service>();
	endPoint_ = std::make_shared<boost::asio::ip::tcp::endpoint>(boost::asio::ip::tcp::v4(), SERVER_PORT);
	acceptor_ = std::make_shared<boost::asio::ip::tcp::acceptor>(*service_, *endPoint_);


	checkNum(argv[0]);
	uint16_t mapHeight = getNumberFromArg_(argv[0]);
	if (mapHeight == 0)
	{
		std::cerr << "map height cannot be 0" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (mapHeight < 20 || mapHeight > 70)
	{
		std::cerr << "map height has to be in range 20-70" << std::endl;
		exit(EXIT_FAILURE);
	}
	checkNum(argv[1]);
	uint16_t mapWidth = getNumberFromArg_(argv[1]);
	if (mapWidth == 0)
	{
		std::cerr << "map width cannot be 0" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (mapWidth < 20 || mapWidth > 100)
	{
		std::cerr << "map width has to be in range 20-100" << std::endl;
		exit(EXIT_FAILURE);
	}

	board_ = std::make_shared<GameBoard>(mapWidth, mapHeight);
}

uint16_t Server::getNumberFromArg_(char *arg)
{
	uint16_t clientsCount = 0;
	std::stringstream ss{arg};
	ss >> clientsCount;
	if (clientsCount == std::numeric_limits<decltype(clientsCount)>::max())
	{
		std::cerr << "Number passed as argument is too big" << std::endl;
		return 0;
	}
	return clientsCount;
}

void Server::acceptClients(char *argv[])
{
	checkNum(argv[0]);
	clientsCount_ = getNumberFromArg_(argv[0]);

	checkNum(argv[1]);
	bots_ = getNumberFromArg_(argv[1]);

	if (bots_ + clientsCount_ > 5)
	{
		std::cerr << "to much players. max: 5" << std::endl;
		exit(EXIT_FAILURE);
	}

	auto clientConnected = std::mem_fn(&Server::clientConnected_);
	for (clientId i = 0; i < clientsCount_; ++i)
	{
		socketPtr newClientSock = std::make_shared<boost::asio::ip::tcp::socket>(*service_);
		clientId newClientId = nextClientId_++;
		acceptor_->async_accept(*newClientSock,
			std::bind(clientConnected, this, newClientSock, newClientId, std::placeholders::_1)); 
	}
	service_->run();
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
	static uint16_t mapStats[2];
	mapStats[0] = board_->getHeight();
	mapStats[1] = board_->getWidth();

	static std::string ackBuff;
	if (ackBuff.empty())
		ackBuff.resize(2);

	boost::system::error_code newErr;
	boost::asio::write(*sock, boost::asio::buffer(mapStats, 4), boost::asio::transfer_exactly(4), newErr);
//	sock->write_some(boost::asio::buffer(mapStats, 4));

	boost::asio::read(*sock, boost::asio::buffer(ackBuff, 2), boost::asio::transfer_exactly(2), newErr);
//	sock->read_some(boost::asio::buffer(ackBuff, 2));
	if (ackBuff != "ok")
		std::cout << "ackBuff != ok [id: " << id << "]" << std::endl;
	else
		std::cout << "init ackBuff ok [id: " << id << "]" << std::endl;
	IController* controller = new ClientController(sock, id);
	std::cout << clientsCount_ << " " << bots_ << std::endl;
	if (clientsCount_ == 1 && bots_ == 0)
	{
		players_.push_back(std::make_shared<Snake>(*board_, controller, make_cord_t(board_->getWidth() / 2 - 4, board_->getHeight() / 2 - 1)));
	}
	else
		players_.push_back(std::make_shared<Snake>(*board_, controller, make_cord_t(id, id * 2)));
	
	controllers_.push_back(controller);
}

void Server::startGame()
{
	for (size_t i = 0; i < players_.size(); ++i)
	{
		std::thread th{&ClientController::run, reinterpret_cast<ClientController*>(players_[i]->getController())};
		th.detach();
	}

	std::cout << "Real clients(players) count: " << players_.size() << std::endl;
	for (clientId i = 0; i < bots_; ++i)
	{
		IController* botController = new ComputerController();
		players_.emplace_back(std::make_shared<Snake>(*board_, botController, make_cord_t(nextClientId_, nextClientId_ + 6 )));
//		players_.push_back(new Snake(*board_, botController, {nextClientId_, nextClientId_ + 6}));
		controllers_.push_back(botController);
		++nextClientId_;
	}

	for (const auto & snake : players_)
		putSnakeToMap(*snake, *board_);

	if (players_.size() == 0)
	{
		std::cerr << "Total amount of players cannot be 0" << std::endl;
		exit(EXIT_FAILURE);
	}
	fruitGenRate = (1.0 / static_cast<double>(players_.size())) * 100.0;

	int fruitAccumulator = 0;
	while (!gameOver_)
	{
		boardLock.lock();
		auto it = players_.begin();
		while (it != players_.end())
		{
			auto& snake = **it;
			auto  toDelete = snake.getLocation();
			snake.move();
			deleteSnakeFromMap(toDelete, *board_);
			putSnakeToMap(snake, *board_);
			if (**it)
				it++;
			else
			{
				deleteSnakeFromMap((*it)->getLocation(), *board_);
				it = players_.erase(it);
			}
		}

		if (!(fruitAccumulator % fruitGenRate))
			(*board_)[rand() % board_->getHeight()]
			[rand() % board_->getWidth()]
			= static_cast<uint8_t>(entityType::food);
		boardLock.unlock();
		++fruitAccumulator;
		std::this_thread::sleep_for(std::chrono::milliseconds(140));
		if (players_.empty())
		{
			gameOver_ = true;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			exit(EXIT_SUCCESS);
		}
	}
}
