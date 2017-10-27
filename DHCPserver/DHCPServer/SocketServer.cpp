#include "SocketServer.h"

socketServer::socketServer()
{

}

int socketServer::socketBind(int port)
{
	//°ó¶¨IPºÍ¶Ë¿Ú
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