#include <iostream>

#include "Client.h"
#include "config.h"

int main(int argc, char **argv){

	std::cout << "starting network interface" << std::endl;

	Client client(HOLE_PUNCH_SERVER_IP, PORT);
	client.start();

	return 0;
}
