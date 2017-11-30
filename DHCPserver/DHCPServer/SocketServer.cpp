#include "SocketServer.h"

socketServer::socketServer()
{
	recvSocket = -1;
}

int socketServer::socketBind(int port)
{
	//��IP�Ͷ˿�
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
		return -1;
	}
}


int socketServer::socketListen(int listenNum)
{
	if (listen(s, listenNum) == SOCKET_ERROR)
	{
		printf("listen error !");
		return -1;
	}
}

SOCKET socketServer::socketAccept()
{
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	recvSocket = accept(s, (SOCKADDR *)&remoteAddr, &nAddrlen);
	return recvSocket;
}

DHCPMessageStuct socketServer::socketRecv(char *RecvData, int Length)
{
	DHCPMessageStuct recvMessage;
	memset(RecvData, 0, Length);     //��ս��ջ���
	memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
	int ret = recv(recvSocket, RecvData, Length, 0);

		memcpy(&recvMessage, RecvData, sizeof(DHCPMessageStuct)); //�ṹ��ת�����ַ���
		return recvMessage;

}

int socketServer::socketSend(DHCPMessageStuct *SendMessage,int Length)
{
	char sendData[2048];
	memcpy(sendData, SendMessage, Length); //�ṹ��ת�����ַ���
	if(send(recvSocket, sendData, 2048, 0)==-1);
		return-1;

		return 0;
}


void socketServer::socketSet(SOCKET S)
{
	recvSocket = S;
}