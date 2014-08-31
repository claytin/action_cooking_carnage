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
	std::cout << "\" from: " << sender_endpoint.address() << std::endl;

	//check if client already exists
	Client *curClient = findClient(sender_endpoint.address().to_string());

	if(curClient == NULL){
		//if it's a new client
		std::cout << "new client" << std::endl;
		curClient = new Client;
		curClient->state = initial;
		curClient->endpoint = &sender_endpoint;
		curClient->address = sender_endpoint.address().to_string();
		clients.push_back(curClient);

		//make sure it's following the protocol (starts with 'hey')
		if(buffer.at(0) == 'h' && buffer.at(1) == 'e' && buffer.at(2) == 'y'){
			socket->send_to(boost::asio::buffer("?v"),
				sender_endpoint);
			curClient->state = getVersion;
		}else{
			//if it doesn't then remove it
			socket->send_to(boost::asio::buffer("sorry bro... wrong protocol"),
				sender_endpoint);
			clients.erase(std::remove(clients.begin(), clients.end(),
				curClient), clients.end());
		}
	}else{
		if(curClient->state == getVersion){
			if(buffer.at(0) == 'v' && buffer.at(1) == ':'){
				
			}else{
				clientError("hmmmm... that's not how version strings look",
					curClient);
			}
		}
	}
}
void HolePunchServer::addClient(Client *client, std::string message){

}

void HolePunchServer::handleClient(Client *client, std::string message){

}

void HolePunchServer::clientError(std::string message, Client *client){
	socket->send_to(boost::asio::buffer("!" + message), *client->endpoint);
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
