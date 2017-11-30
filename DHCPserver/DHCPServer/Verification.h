#pragma once
//增加验证信息类，增加验证环节
#include "DHCPDataStruct.h"
#include "SocketServer.h"
class Verifiction
{
public:
	Verifiction();
	void begin(char *question, char *answer);
	int sendQuestiooon(SOCKET s);
	bool ckeck(SOCKET s);

private:
	VerifictionData VerifictionServer;
	char sendData[1024];
	char recvData[2048];

};
