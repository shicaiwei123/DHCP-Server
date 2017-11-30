#pragma once
#include "SocketBasic.h"
#include "DHCPDataStruct.h"
//#include <Winsock2.h>
//#include<stdio.h>

class socketServer : public socketBasic
{
public:
	socketServer();
	int socketBind(int port);
	int socketListen(int listenNum);
	SOCKET socketAccept();            //侦听到请求，建立socket连接进行通信
	DHCPMessageStuct socketRecv(char *RecvData, int Length);
	int socketSend(DHCPMessageStuct *SendMessage, int Length);
	void socketSet(SOCKET S);     //对内部通信的socket套接字进行赋值

	//int socketRecv();
private:
	SOCKET recvSocket;
};