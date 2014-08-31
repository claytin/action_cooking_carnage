#include "Client.h"

Client::Client(std::string _HolePunchHostName, int _port):
	HolePunchHostName(_HolePunchHostName),
	port(_port){

}

Client::~Client(void){

}

void Client::start(void){
	try{
		boost::asio::io_service io_service;

		udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

		udp::resolver resolver(io_service);
		udp::resolver::query query(udp::v4(), HolePunchHostName, "2048");
		udp::resolver::iterator iterator = resolver.resolve(query);

		//char request[1024];
		std::cout << "Enter message: " << std::endl;
		std::string request;
		std::cin >> request;
		std::cout << "requesting: " << request << std::endl;

		size_t request_length = request.length();
		s.send_to(boost::asio::buffer(request, request_length), *iterator);

		char reply[1024];
		udp::endpoint sender_endpoint;
		size_t reply_length = s.receive_from(
			boost::asio::buffer(reply, 1024), sender_endpoint);
		std::cout << "Reply is: ";
		std::cout.write(reply, reply_length);
		std::cout << "\n";
	}catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
