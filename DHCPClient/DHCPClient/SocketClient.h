#pragma once
#include "SocketBasic.h"

class socketClient :public socketBasic
{
public:
	socketClient();
	int socketConnect(const char *ip, int port);//绑定套接字要访问的服务器参数
	//int socketSend(*sendData);

};
