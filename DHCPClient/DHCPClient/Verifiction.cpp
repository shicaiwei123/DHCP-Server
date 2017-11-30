#include "Verification.h"

Verifiction::Verifiction()
{

}

void Verifiction::begin()
{
	memset(sendData, 0, sizeof(sendData));
	memset(recvData, 0,sizeof(recvData));

	verPass = 0;
}

int Verifiction::recvQuestion(SOCKET s)
{

	memset(recvData, 0, 2048);     //清空接收缓存
	int ret = recv(s, recvData, 2048, 0);
	
	if (ret > 0)
	{
		cout << "请输入验证码："
			<<recvData<<endl;
		return true;
	}

	else
		return false;
}

bool Verifiction::sendAnswer(SOCKET s)
{
	char anwser[7];
	cin >> sendData;
	if (send(s, sendData, 1024, 0) == -1);
	return -1;

	return 0;
}

bool Verifiction::ckeck(SOCKET s)
{

	memset(recvData, 0, 2048);     //清空接收缓存
	int ret = recv(s, recvData, 2048, 0);

	if (ret > 0)
	{
		verPass=!(strcmp(recvData, "YES"));
		if (verPass == 1)
		{
			verPass = 0;
			return true;
		}

		else
			return false;
	}

	else
		return false;
}


