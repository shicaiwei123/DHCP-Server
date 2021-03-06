
//#include <cstdio>

#include <string.h>
#include <memory.h>
#include "SocketServer.h"
#include "DHCPDataStruct.h"
#include "DHCPPackageServer.h"
#pragma comment(lib,"ws2_32.lib")
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP
DHCPMessageStuct messageTemp;


 //typedef struct send_info
 //{
	// char info_from[20]; //发送者ID
	// char info_to[20]; //接收者ID
	// char info_content[256]; //消息主体 
	// int info_length; //发送的消息主体的长度

 //}recv_info;




int main(int argc, char* argv[])
{
	char sendData[4096];
	char revData[8192];
	DHCPMessageStuct sendMessage;
	DHCPMessageStuct recvMessage;
	memset(&recvMessage, 0, sizeof(recvMessage));
	//DHCPMessageStuct *DHCPMessage = &message;
	DHCPPackageServer serverPackage(&sendMessage,DHCP_OFFER);
	int err;
	socketServer serverSocket;
	err=serverSocket.begin();
	if (err==-1)
	{
		cout << "初始化失败";
	}
	err=serverSocket.socketCreate(TCP);
	if (err == -1)
	{
		cout << "创建套接字失败";
	}
	err=serverSocket.socketBind(8888);
	if (err == -1)
	{
		cout << "绑定套接字失败";
	}
	err=serverSocket.socketListen(5);
	if (err == -1)
	{
		cout << "侦听套接字失败";
	}
	SOCKET slisten = serverSocket.socketGet();
	//循环接收数据
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	while (true)
	{
		printf("等待连接...\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
		memset(revData, 0, sizeof(revData));     //清空缓存
		//memset(&sendMessage, 0, sizeof(sendMessage));
		//memset(&messageTemp, 0, sizeof(messageTemp));

		//接收数据
		int ret = recv(sClient, revData, sizeof(revData), 0);
		if (ret > 0)
		{
			//revData[ret] = 0x00;
			//printf(revData);
			memcpy(&recvMessage, revData, sizeof(revData));//把接收到的信息转换成结构体
		//	messageTemp = recvMessage;
			serverPackage.analysis(&messageTemp);
		}

		//发送数据
		serverPackage.package(&sendMessage, DHCP_OFFER);
		memcpy(sendData, &sendMessage, sizeof(sendMessage));//把接收到的信息转换成结构体
		//char * sendData = "你好，TCP客户端！\n";
		send(sClient, sendData, sizeof(sendData), 0);
		closesocket(sClient);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
