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
	int sendAnwser(SOCKET s);

private:
	VerifictionData VerifictionClient;
	char sendData[1024];
	char recvData[2048];
	int answerLen;
	char question[7];
	char answer[7];

};
