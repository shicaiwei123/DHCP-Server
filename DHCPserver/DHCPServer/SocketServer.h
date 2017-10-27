#pragma once
#include "SocketBasic.h"
//#include <Winsock2.h>
//#include<stdio.h>

class socketServer : public socketBasic
{
public:
	socketServer();
	int socketBind(int port);
	int socketListen(int listenNum);
	//int socketRecv();
};