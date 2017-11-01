#pragma once
//继承socket基类，结合客户端需求，增加了一些方法
//连接建立
//报文收发
#include "SocketBasic.h"
#include "DHCPDataStruct.h"
class socketClient :public socketBasic
{
public:
	socketClient();
	int socketConnect(const char *ip, int port);//绑定套接字要访问的服务器参数
	DHCPMessageStuct socketRecv(char *RecvData, int Length);
	int socketSend(DHCPMessageStuct *SendMessage, int Length);
	//int socketSend(*sendData);

};
