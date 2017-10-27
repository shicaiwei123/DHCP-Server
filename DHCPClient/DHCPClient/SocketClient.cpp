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


