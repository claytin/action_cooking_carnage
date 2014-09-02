#include "Client.h"

Client::Client(std::string _HolePunchHostName, int _port):
	HolePunchHostName(_HolePunchHostName),
	port(_port){

}

Client::~Client(void){

}

void Client::start(void){
	try{
		//create stocket and stuff
		boost::asio::io_service io_service;

		socket = new udp::socket(io_service, udp::endpoint(udp::v4(), 0));

		udp::resolver resolver(io_service);
		udp::resolver::query query(udp::v4(), HolePunchHostName, "2048");
		iterator = resolver.resolve(query);

		//start handshake with hole punch server
		handshake();
	}catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}
}

void Client::handshake(void) throw(std::exception){
	//start handshake with 'hey'
	std::cout << "establishing connection..." << std::endl;
	std::string request = "hey";

	size_t request_length = request.length();
	socket->send_to(boost::asio::buffer(request, request_length), *iterator);

	char reply[1024];
	udp::endpoint sender_endpoint;
	size_t reply_length = socket->receive_from(
		boost::asio::buffer(reply, 1024), sender_endpoint);
	std::cout.write(reply, reply_length);
}

void Client::parseMesg(std::string mesg){
	std::cout << mesg << std::endl;
}
