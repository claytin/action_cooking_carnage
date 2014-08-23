#ifndef HOLEPUNCHSERVER_H
#define HOLEPUNCHSERVER_H

class HolePunchServer{

public:
	HolePunchServer(int _port);
	~HolePunchServer(void);
	void start(void);

private:
	int port;
};

#endif
