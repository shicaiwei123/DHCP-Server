#include "Verification.h"

Verifiction::Verifiction()
{

}

void Verifiction::begin(char *Question, char *Answer)
{
	memset(&VerifictionServer, 0, sizeof(VerifictionData));
	memset(sendData, 0, sizeof(sendData));
	memset(recvData, 0,sizeof(recvData));
	memcpy(VerifictionServer.question, Question, 7);
	memcpy(VerifictionServer.answer, Answer, 7);
}

int Verifiction::sendQuestiooon(SOCKET s)
{
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
	{
		send(s, "YES", 4, 0);
		return true;
	}	
	else
	{
		send(s, "NO", 3, 0);
		return false;
	}

}


