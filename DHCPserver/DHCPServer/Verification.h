#pragma once
//������֤��Ϣ�࣬������֤����
#include "DHCPDataStruct.h"
#include "SocketServer.h"
class Verifiction
{
public:
	Verifiction();
	void begin();
	int sendQuestiooon(SOCKET s, char *question, char *answer);
	bool ckeck(SOCKET s);

private:
	VerifictionData VerifictionServer;
	char sendData[1024];
	char recvData[2048];
	int answerLen;

};
