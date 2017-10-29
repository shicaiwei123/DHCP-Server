#include "SocketClient.h"

socketClient::socketClient()
{

}

int socketClient::socketConnect(const char *ip, int port)
{
	int err;
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	err = connect(s, (sockaddr *)&serAddr, sizeof(serAddr));
	if(err==SOCKET_ERROR)
	{
		printf("connect error !");
		closesocket(s);
		return -1;
	}
}

DHCPMessageStuct socketClient::socketRecv(char *RecvData, int Length)
{
	DHCPMessageStuct recvMessage;
	memset(RecvData, 0, Length);     //��ս��ջ���
	memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
	int ret = recv(s, RecvData, Length, 0);

	memcpy(&recvMessage, RecvData, sizeof(DHCPMessageStuct)); //�ṹ��ת�����ַ���
	return recvMessage;

}

int socketClient::socketSend(DHCPMessageStuct *SendMessage, int Length)
{
	char sendData[2048];
	memcpy(sendData, SendMessage, Length); //�ṹ��ת�����ַ���
	if (send(s, sendData, 2048, 0) == -1);
	return-1;

	return 0;
}


