#ifndef HOLEPUNCHSERVER_H
#define HOLEPUNCHSERVER_H

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class HolePunchServer{

enum ClientState {
	initial, //when first establishing connection
	getVersion,
};

struct Client{
	std::string address;
	ClientState state;
	udp::endpoint *endpoint;
};

public:
	HolePunchServer(int _port);
	~HolePunchServer(void);
	void start(void);

private:
	void listenForClients();
	Client* findClient(std::string address);
	void removeClient(Client *client);
	void clientError(std::string errorMessage, Client *client);
	void addClient(Client *client, std::string message);
	void handleClient(Client *client, std::string message);

	udp::socket *socket;
	int port;
	std::vector<Client*> clients;

};

#endif

//just gonna put a reference thing here
//!<error> - error message
//?<question> - question (should get a reply)
//hey - the initial message
//<var>:<value> - tell client what <var>'s value is (or the other way around)
//
//questions:
//v - ask for version (repsonse should be v:<version>)
