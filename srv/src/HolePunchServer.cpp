#include "HolePunchServer.h"

HolePunchServer::HolePunchServer(int _port):
	port(_port){

}

HolePunchServer::~HolePunchServer(void){

}

void HolePunchServer::start(void){
	boost::asio::io_service io;

	socket = new udp::socket(io, udp::endpoint(udp::v4(), port));

	while(true){
		listenForClients();
	}
}

void HolePunchServer::listenForClients(){
	//std::string buffer;
	udp::endpoint sender_endpoint;
	std::vector<char> buffer(1024);
	socket->receive_from(boost::asio::buffer(buffer), sender_endpoint);

	std::cout << "received: \"";
	for(unsigned int i = 0; i < buffer.size(); i++){
		std::cout << buffer.at(i);
	}
	std::cout << "\" from: " << sender_endpoint.address() << "@"
		<< sender_endpoint.port()  << std::endl;

	//check if client already exists
	Client *curClient = findClient(sender_endpoint.address().to_string());

	//char vectore or message string
	std::string message(buffer.begin(), buffer.end());

	if(curClient == NULL){
		//time to create a new client
		addClient(&sender_endpoint, message);
	}else{
		handleClient(curClient, message);
	}
}
void HolePunchServer::addClient(udp::endpoint *endpoint, std::string message){
	std::cout << "new client" << std::endl;
	Client *client = new Client;
	client->state = initial;
	client->endpoint = endpoint;
	client->address = endpoint->address().to_string();
	clients.push_back(client);

	//make sure it's following the protocol (starts with 'hey')
	if(message[0] == 'h' && message[1] == 'e' && message[2] == 'y'){
		socket->send_to(boost::asio::buffer("?v"),
			*endpoint);
		client->state = getVersion;
	}else{
		//if it doesn't then kill it
		clientError("sorry bro... wrong protocol", client);
	}

}

void HolePunchServer::handleClient(Client *client, std::string message){
	if(client->state == getVersion){
		//should be getting version info
		if(message.length() > 2 && message[0] == 'v' && message[1] == ':'){
			//make sure the version are the same
			std::cout << message.substr(2, -1).compare(VERSION_STRING) << std::endl;
			if(!message.substr(2, -1).compare(VERSION_STRING)){
				std::cout << "yep" << std::endl;
				clientError("nice version bro", client);
			}else{
				clientError("ur version number isn't right", client);
			}
		}else{
			clientError("hmmmm... that's not how version strings look", client);
		}
	}
}

void HolePunchServer::clientError(std::string message, Client *client){
	socket->send_to(boost::asio::buffer("!" + message +
		"\nclosing connetion (as if there ever was one)"), *client->endpoint);
	removeClient(client);
}

void HolePunchServer::removeClient(Client *client){
	clients.erase(std::remove(clients.begin(), clients.end(), client),
		clients.end());
}

HolePunchServer::Client* HolePunchServer::findClient(std::string address){
	Client *client = NULL;
	for(std::vector<Client*>::iterator it = clients.begin();
		it != clients.end(); ++it){
		if(address == (*it)->address){
			std::cout << "existing client" << std::endl;
			client = *it;
		}
	}

	return client;
}
