#include "Verification.h"

Verifiction::Verifiction()
{

}

void Verifiction::begin()
{
	memset(&VerifictionClient, 0, sizeof(VerifictionData));
	memset(question, 0, sizeof(question));
	memset(answer, 0, sizeof(question));

}

int Verifiction::recvQuestion(SOCKET s)
{

	memset(recvData, 0, 2048);     //��ս��ջ���
	memset(question, 0, sizeof(question));
	int ret = recv(s, recvData, 2048, 0);

	memcpy(question, recvData, sizeof(question)); //�ṹ��ת�����ַ���
	cout << question;
	
	if (ret == -1);
	return-1;
	return 0;
}

int Verifiction::sendAnwser(SOCKET s)
{
	memset(answer, 0, sizeof(answer));     //��ս��ջ���
	cout << "��������֤�룺"<<endl;
	cin >> answer;

	memcpy(sendData, answer, sizeof(answer)); //�ṹ��ת�����ַ���
	if (send(s, sendData, 2048, 0) == -1);
	return-1;

	return 0;
}


