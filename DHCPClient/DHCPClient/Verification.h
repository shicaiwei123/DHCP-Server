#pragma once
//������֤��Ϣ�࣬������֤����
#include "DHCPDataStruct.h"
#include "SocketClient.h"
class Verifiction
{
public:
	Verifiction();
	void begin();
	int recvQuestion(SOCKET s);
	bool sendAnswer(SOCKET s);
	bool ckeck(SOCKET s);

private:
	VerifictionData VerifictionClient;
	char sendData[1024];
	char recvData[2048];
	int verPass;

};
