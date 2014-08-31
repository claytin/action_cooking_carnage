#include "HolePunchServer.h"

HolePunchServer::HolePunchServer(int _port):
	port(_port){

}

HolePunchServer::~HolePunchServer(void){

}

void HolePunchServer::start(void){
	boost::asio::io_service io;

	udp::socket socket(io, udp::endpoint(udp::v4(), port));
	//int max_length = 1024;
	while(true){
		//std::string buffer;
		udp::endpoint sender_endpoint;
		std::vector<char> buffer(1024);
		socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);

		std::cout << "recieved: \"";
		for(unsigned int i = 0; i < buffer.size(); i++){
			std::cout << buffer.at(i);
		}
		std::cout << "\" from: " << sender_endpoint.address() << std::endl;

		socket.send_to(boost::asio::buffer(buffer), sender_endpoint);
	}
}
