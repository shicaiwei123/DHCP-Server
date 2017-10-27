#include "SocketBasic.h"

socketBasic::socketBasic()
{

}

int socketBasic::begin()
{

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
}
int socketBasic::socketCreate(int protocol)
{
	if (protocol == IPPROTO_TCP)
	{
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			printf("invalid socket !");
			return -1;
		}

	}
	else if (protocol == IPPROTO_UDP)
	{
		s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (s == INVALID_SOCKET)
		{
			printf("invalid socket !");
			return -1;
		}
	}
	else
		return -2;


}

SOCKET socketBasic::socketGet()
{
	return s;
}





