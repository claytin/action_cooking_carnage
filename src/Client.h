#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class Client{

public:
	Client(std::string _HolePunchHostName, int _port);
	~Client(void);
	void start(void);

private:
	std::string HolePunchHostName;
	int port;
};

#endif
