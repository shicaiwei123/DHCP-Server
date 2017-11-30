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
	SOCKET socketAccept();            //���������󣬽���socket���ӽ���ͨ��
	DHCPMessageStuct socketRecv(char *RecvData, int Length);
	int socketSend(DHCPMessageStuct *SendMessage, int Length);
	void socketSet(SOCKET S);     //���ڲ�ͨ�ŵ�socket�׽��ֽ��и�ֵ

	//int socketRecv();
private:
	SOCKET recvSocket;
};