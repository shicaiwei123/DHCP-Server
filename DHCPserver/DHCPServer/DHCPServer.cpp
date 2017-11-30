
//#include <cstdio>
#include <string.h>

#include <memory.h>
#include "SocketServer.h"
#include"DHCPPackageServer.h"
#include "TimeCounter.h"
#include "Verification.h"
#include <process.h>  
#include <windows.h>  
#pragma comment(lib,"ws2_32.lib")
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP
DataManege dataServer;

 typedef struct send_info
 {
	 char info_from[20]; //发送者ID
	 char info_to[20]; //接收者ID
	 char info_content[256]; //消息主体 
	 int info_length; //发送的消息主体的长度

 }recv_info;

 struct threadPara
 {
	 socketServer serversocketthread;
	 SOCKET socketthread;
 };




 //定义一个接收线程
 DWORD WINAPI ClientRecvThread(LPVOID lpParameter)
//unsigned int __stdcall ThreadFun(void *lpParameter)
 {

	 SOCKET sClient = (SOCKET)lpParameter;
	 uint8_t time[3] = { 0,1,0 };   //时分秒
	 HANDLE timeThread[2];
	 int timecut = 0;
	 bool DHCPFinish = false;
	 char recvData[4096];
	 char sendData[2048];
	 memset(recvData, 0, sizeof(recvData));
	 memset(recvData, 0, sizeof(recvData));

	 DHCPMessageStuct sendMessage;
	 DHCPMessageStuct recvMessage;
	 DHCPMessageStuct tempMessage;

	 DHCPPackageServer packageServer(&sendMessage);
	 packageServer.begin();
	 packageServer.setData(&dataServer);

	 Clock clock(&dataServer);
	 clock.begin();
	 socketServer serverSocketThread;
	 serverSocketThread.begin();
	 serverSocketThread.socketSet(sClient);



	 while(1)
	 { 

		 //接收数据
		 recvMessage = serverSocketThread.socketRecv(recvData, sizeof(recvData));
		 packageServer.analysis(&recvMessage);
		 packageServer.package(&sendMessage);
		 //发送数据
		 serverSocketThread.socketSend(&sendMessage, 2048);
		 DHCPFinish = packageServer.getState();
		 if (DHCPFinish)//如果完成了配置那么就重置定时器
		 {
	 		clock.set(0, 1, 0);
			clock.setMac((char*)(&sendMessage.hdr.chaddr));
			clock.run();//发送ACK后开启定时器		 	continue;
		 }

		 //接收数据

		 recvMessage = serverSocketThread.socketRecv(recvData, sizeof(recvData));
		 packageServer.analysis(&recvMessage);
		 memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
		 packageServer.package(&sendMessage);
		 //发送数据
		 serverSocketThread.socketSend(&sendMessage, 2048);
		 DHCPFinish = packageServer.getState();
		 if (DHCPFinish)//如果完成了配置那么就重置定时器
		 {
	 		clock.set(0, 1, 0);
			clock.setMac((char*)(&sendMessage.hdr.chaddr));
			clock.run();//发送ACK后开启定时器

		 }
	 }
	 closesocket(sClient);
	 return 0;
 }


int main(int argc, char* argv[])
{
	//uint8_t time[3] = {0,1,0};   //时分秒
	//bool DHCPFinish = false;
	//bool verPass = false;
	//uint8_t verCounter = 1;
	//char recvData[4096];
	//char sendData[2048];
	//char question[7] = "ABCDEF";
	//char answer[7] = "ABCDEF";
	//DHCPMessageStuct sendMessage;
	//DHCPMessageStuct recvMessage;
	//DHCPMessageStuct tempMessage;
	//Verifiction VerifictionServer;
	//DHCPPackageServer packageServer(&sendMessage);
	//packageServer.begin(time);
	//VerifictionServer.begin(question, answer);
	//Clock clock;
	//clock.set(0, 1, 0);//初始化定时器为1分钟
	dataServer.begin();
	char question[7] = "ABCDEF";
	char answer[7] = "ABCDEF";
	bool verPass = false;
	uint8_t verCounter = 1;
	Verifiction VerifictionServer;
	VerifictionServer.begin(question, answer);
	const int THREAD_NUM = 5;
	HANDLE handle[THREAD_NUM];
	int i = 0;
	int err;
	dataServer.begin();
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
		//进行验证
		while (!verPass)
		{
			VerifictionServer.sendQuestiooon(sClient);
			verPass = VerifictionServer.ckeck(sClient);
			verCounter++;
			if (verCounter > 5)
			{

				closesocket(sClient);
				break;

			}
		}
		verPass = false;

		if (verCounter > 5)   //超过五次验证不成功，则断开连接，重新等待新的连接
		{
			cout << "验证失败" << endl;
			verCounter = 0;
			continue;
		}
		//创建线程
		handle[i] = CreateThread(NULL, 0, ClientRecvThread, (LPVOID)sClient, 0, NULL);
		i = i + 1;
		WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
		//CloseHandle(handle[1]);
		////进行验证
		//while (!verPass)
		//{
		//	VerifictionServer.sendQuestiooon(sClient);
		//	verPass = VerifictionServer.ckeck(sClient);
		//	verCounter++;
		//	if (verCounter>5)
		//	{
		//		closesocket(sClient);
		//		break;

		//	}
		//}
		//verPass = false;
		//if (verCounter>5)   //超过五次验证不成功，则断开连接，重新等待新的连接
		//{
		//	cout << "验证失败" << endl;
		//	continue;
		//}



	
		//	//接收数据
		//recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		//packageServer.analysis(&recvMessage);
		//packageServer.package(&sendMessage);
		//	//发送数据
		//serverSocket.socketSend(&sendMessage,2048);
		//DHCPFinish = packageServer.getState();
		////if (DHCPFinish)//如果完成了配置那么就重置定时器
		////{
		////	clock.set(0, 1, 0);
		////	clock.run();//发送ACK后开启定时器
		////	break;
		////}

		////接收数据

		//recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		//packageServer.analysis(&recvMessage);
		//memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
		//packageServer.package(&sendMessage);
		////发送数据
		//serverSocket.socketSend(&sendMessage, 2048);
		//DHCPFinish = packageServer.getState();
		////if (DHCPFinish)//如果完成了配置那么就重置定时器
		////{
		////	clock.set(0, 1, 0);
		////	clock.run();//发送ACK后开启定时器
		////}
		//closesocket(sClient);

	
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
