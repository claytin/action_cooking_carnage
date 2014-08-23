#include <iostream>

#include "HolePunchServer.h"
#include "config.h"

int main(int argc, char **argv){

	std::cout << "starting hole punch server" << std::endl;

	HolePunchServer server(PORT);
	server.start();

	return 0;
}
