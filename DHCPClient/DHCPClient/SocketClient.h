#pragma once
#include "SocketBasic.h"

class socketClient :public socketBasic
{
public:
	socketClient();
	int socketConnect(const char *ip, int port);//���׽���Ҫ���ʵķ���������
	//int socketSend(*sendData);

};
