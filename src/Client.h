#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client{

public:
	Client(std::string _HolePunchHostName, int _port);
	~Client(void);
	void start(void);

private:
	std::string HolePunchHostName;
	int port;
};

#endif
