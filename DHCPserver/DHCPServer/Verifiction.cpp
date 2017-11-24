#include "Verification.h"

Verifiction::Verifiction()
{

}

void Verifiction::begin()
{
	memset(&VerifictionServer, 0, sizeof(VerifictionData));
}

int Verifiction::sendQuestiooon(SOCKET s,char *question, char *answer)
{

	memcpy(VerifictionServer.question, question, sizeof(VerifictionServer.question));
	memcpy(VerifictionServer.answer, answer, sizeof(VerifictionServer.answer));

	memcpy(sendData, VerifictionServer.question, sizeof(VerifictionServer.question)); //结构体转换成字符串
	if (send(s, sendData, 1024, 0) == -1);
	return-1;
	return 0;
}

bool Verifiction::ckeck(SOCKET s)
{
	int flag;
	char recvAnwser[7];
	memset(recvData,0,2048);     //清空接收缓存
	int ret = recv(s, recvData, 2048, 0);
	memcpy(recvAnwser, recvData, 7); //字符串转数组
	flag = strcmp(recvAnwser, VerifictionServer.answer);
	if (flag == 0)
		return true;
	else
	return false;
}


