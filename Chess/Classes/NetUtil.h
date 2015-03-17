#ifndef _NetUtil_H_
#define _NetUtil_H_
class NetUtil
{
public:
	NetUtil();
	~NetUtil();
	bool listen(short port);
	bool accecpt();

	int send(const char* buf, int size);
	bool recv();


	bool connect(short port, const char* ip);
public:
	static char packet[4];
	int recvlen;
	int server;
	int client;
};
#endif
