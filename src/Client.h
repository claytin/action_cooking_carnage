#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <exception>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class Client{

struct Peer{
	udp::endpoint endpoint;
};

public:
	Client(std::string _HolePunchHostName, int _port);
	~Client(void);
	void start(void);

private:
	void handshake(void) throw(std::exception);
	void sendToPeer(Peer *peer);
	void parseMesg(std::string mesg);

	std::vector<Peer> peers;
	std::string HolePunchHostName;
	int port;
	udp::socket *socket;
	udp::resolver::iterator iterator;
};

#endif
