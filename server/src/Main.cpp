#include <iostream>
#include "HolePunchServer.h"

int main(int argc, char **argv){

	std::cout << "starting hole punch server" << std::endl;

	HolePunchServer server;
	server.start();

	return 0;
}
