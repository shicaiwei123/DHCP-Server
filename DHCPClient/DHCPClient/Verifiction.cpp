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

	memset(recvData, 0, 2048);     //清空接收缓存
	memset(question, 0, sizeof(question));
	int ret = recv(s, recvData, 2048, 0);

	memcpy(question, recvData, sizeof(question)); //结构体转换成字符串
	cout << question;
	
	if (ret == -1);
	return-1;
	return 0;
}

int Verifiction::sendAnwser(SOCKET s)
{
	memset(answer, 0, sizeof(answer));     //清空接收缓存
	cout << "请输入验证码："<<endl;
	cin >> answer;

	memcpy(sendData, answer, sizeof(answer)); //结构体转换成字符串
	if (send(s, sendData, 2048, 0) == -1);
	return-1;

	return 0;
}


