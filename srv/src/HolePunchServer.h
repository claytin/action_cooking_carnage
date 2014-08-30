#ifndef HOLEPUNCHSERVER_H
#define HOLEPUNCHSERVER_H

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class HolePunchServer{

public:
	HolePunchServer(int _port);
	~HolePunchServer(void);
	void start(void);

private:
	int port;
};

#endif
