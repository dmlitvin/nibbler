#pragma once

# include "Server.hpp"
//# include "IController.hpp"
//# include <boost/asio.hpp>

enum class Key
{
	UP, DOWN, LEFT, RIGHT
};

class ClientController : public IController
{
public:
	using clientId = uint16_t;
	using socketPtr = std::shared_ptr<boost::asio::ip::tcp::socket> ;

	explicit ClientController(socketPtr sock);
	ClientController() = delete;
	ClientController(const ClientController &rhs) = delete;
	ClientController &operator=(const ClientController &rhs) = delete;
	~ClientController() = default;

	void setDirectionControl(direction_t &direction) override;
	void setGameBoard(const GameBoard &board) override;
	void updateDirection(cord_t cord) override;
	void run();

private:
	Key					lastPressed_;
	direction_t*		direction_;
	const GameBoard*	gameBoard_;
	socketPtr sock_;
};


