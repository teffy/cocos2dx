#include "NetUtil.h"
#include <netowrk/Sock>

NetUtil::NetUtil()
{
	server = -1;
	client = -1;
}


NetUtil::~NetUtil()
{
}

bool NetUtil::listen(short port){
	if (server == -1){
		server = socket
			return true;
	}
	else{
		return false;
	}
}