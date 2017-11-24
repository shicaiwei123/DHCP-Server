
//#include <cstdio>
#include <string.h>

#include <memory.h>
#include "SocketServer.h"
#include"DHCPPackageServer.h"
#include "TimeCounter.h"
#include "Verification.h"
#pragma comment(lib,"ws2_32.lib")
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP


 typedef struct send_info
 {
	 char info_from[20]; //发送者ID
	 char info_to[20]; //接收者ID
	 char info_content[256]; //消息主体 
	 int info_length; //发送的消息主体的长度

 }recv_info;




int main(int argc, char* argv[])
{
	uint8_t time[3] = {0,1,0};
	bool DHCPFinish = false;
	char recvData[4096];
	char sendData[2048];
	VerifictionData VerifictionDataServer;
	Verifiction VerifictionServer;
	DHCPMessageStuct sendMessage;
	DHCPMessageStuct recvMessage;
	DHCPMessageStuct tempMessage;
	DHCPPackageServer packageServer(&sendMessage);
	packageServer.begin(time);
	VerifictionServer.begin();
	Clock clock;
	clock.set(0, 1, 0);//初始化定时器为1分钟
	memcpy(VerifictionDataServer.question, "ABCDEF", 7);
	memcpy(VerifictionDataServer.answer, "ABCDEF", 7);
	int VerFlag = 0;
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
	//sockaddr_in remoteAddr;
	//int nAddrlen = sizeof(remoteAddr);
	
	while (true)
	{
		cout<<"等待连接...\n";
		sClient = serverSocket.socketAccept();
		if (sClient == -1)
		{
			cout<<"accept error !"<<endl;
			continue;
		}
		cout<<"接受到一个连接,标号为："<<sClient<<endl;
	
			//接收数据
		recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		packageServer.analysis(&recvMessage);
		packageServer.package(&sendMessage);
			//发送数据
		serverSocket.socketSend(&sendMessage,2048);
		DHCPFinish = packageServer.getState();
		//if (DHCPFinish)//如果完成了配置那么就重置定时器
		//{
		//	clock.set(0, 1, 0);
		//	clock.run();//发送ACK后开启定时器
		//	break;
		//}

		//接收数据

		recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		packageServer.analysis(&recvMessage);
		memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
		packageServer.package(&sendMessage);
		while (!VerFlag)
		{
			//发送数据
			VerifictionServer.sendQuestiooon(slisten, VerifictionDataServer.question, VerifictionDataServer.answer);

			//接收验证
			VerFlag = VerifictionServer.ckeck(slisten);
		}

		serverSocket.socketSend(&sendMessage, 2048);
		DHCPFinish = packageServer.getState();
		//if (DHCPFinish)//如果完成了配置那么就重置定时器
		//{
		//	clock.set(0, 1, 0);
		//	clock.run();//发送ACK后开启定时器
		//}
		closesocket(sClient);

	
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
