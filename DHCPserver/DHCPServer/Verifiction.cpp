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

	memcpy(sendData, VerifictionServer.question, sizeof(VerifictionServer.question)); //�ṹ��ת�����ַ���
	if (send(s, sendData, 1024, 0) == -1);
	return-1;
	return 0;
}

bool Verifiction::ckeck(SOCKET s)
{
	int flag;
	char recvAnwser[7];
	memset(recvData,0,2048);     //��ս��ջ���
	int ret = recv(s, recvData, 2048, 0);
	memcpy(recvAnwser, recvData, 7); //�ַ���ת����
	flag = strcmp(recvAnwser, VerifictionServer.answer);
	if (flag == 0)
		return true;
	else
	return false;
}


