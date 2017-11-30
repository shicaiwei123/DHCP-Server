
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
	 char info_from[20]; //������ID
	 char info_to[20]; //������ID
	 char info_content[256]; //��Ϣ���� 
	 int info_length; //���͵���Ϣ����ĳ���

 }recv_info;

 struct threadPara
 {
	 socketServer serversocketthread;
	 SOCKET socketthread;
 };




 //����һ�������߳�
 DWORD WINAPI ClientRecvThread(LPVOID lpParameter)
//unsigned int __stdcall ThreadFun(void *lpParameter)
 {

	 SOCKET sClient = (SOCKET)lpParameter;
	 uint8_t time[3] = { 0,1,0 };   //ʱ����
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

		 //��������
		 recvMessage = serverSocketThread.socketRecv(recvData, sizeof(recvData));
		 packageServer.analysis(&recvMessage);
		 packageServer.package(&sendMessage);
		 //��������
		 serverSocketThread.socketSend(&sendMessage, 2048);
		 DHCPFinish = packageServer.getState();
		 if (DHCPFinish)//��������������ô�����ö�ʱ��
		 {
	 		clock.set(0, 1, 0);
			clock.setMac((char*)(&sendMessage.hdr.chaddr));
			clock.run();//����ACK������ʱ��		 	continue;
		 }

		 //��������

		 recvMessage = serverSocketThread.socketRecv(recvData, sizeof(recvData));
		 packageServer.analysis(&recvMessage);
		 memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
		 packageServer.package(&sendMessage);
		 //��������
		 serverSocketThread.socketSend(&sendMessage, 2048);
		 DHCPFinish = packageServer.getState();
		 if (DHCPFinish)//��������������ô�����ö�ʱ��
		 {
	 		clock.set(0, 1, 0);
			clock.setMac((char*)(&sendMessage.hdr.chaddr));
			clock.run();//����ACK������ʱ��

		 }
	 }
	 closesocket(sClient);
	 return 0;
 }


int main(int argc, char* argv[])
{
	//uint8_t time[3] = {0,1,0};   //ʱ����
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
	//clock.set(0, 1, 0);//��ʼ����ʱ��Ϊ1����
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
		cout << "��ʼ��ʧ��";
	}
	err=serverSocket.socketCreate(TCP);
	if (err == -1)
	{
		cout << "�����׽���ʧ��";
	}
	err=serverSocket.socketBind(8888);
	if (err == -1)
	{
		cout << "���׽���ʧ��";
	}
	err=serverSocket.socketListen(5);
	if (err == -1)
	{
		cout << "�����׽���ʧ��";
	}
	SOCKET slisten = serverSocket.socketGet();
	//ѭ����������
	SOCKET sClient;


	
	while (true)
	{
		cout<<"�ȴ�����...\n";
		sClient = serverSocket.socketAccept();
		if (sClient == -1)
		{
			cout<<"accept error !"<<endl;
			continue;
		}
		cout<<"���ܵ�һ������,���Ϊ��"<<sClient<<endl;
		//������֤
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

		if (verCounter > 5)   //���������֤���ɹ�����Ͽ����ӣ����µȴ��µ�����
		{
			cout << "��֤ʧ��" << endl;
			verCounter = 0;
			continue;
		}
		//�����߳�
		handle[i] = CreateThread(NULL, 0, ClientRecvThread, (LPVOID)sClient, 0, NULL);
		i = i + 1;
		WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
		//CloseHandle(handle[1]);
		////������֤
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
		//if (verCounter>5)   //���������֤���ɹ�����Ͽ����ӣ����µȴ��µ�����
		//{
		//	cout << "��֤ʧ��" << endl;
		//	continue;
		//}



	
		//	//��������
		//recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		//packageServer.analysis(&recvMessage);
		//packageServer.package(&sendMessage);
		//	//��������
		//serverSocket.socketSend(&sendMessage,2048);
		//DHCPFinish = packageServer.getState();
		////if (DHCPFinish)//��������������ô�����ö�ʱ��
		////{
		////	clock.set(0, 1, 0);
		////	clock.run();//����ACK������ʱ��
		////	break;
		////}

		////��������

		//recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		//packageServer.analysis(&recvMessage);
		//memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
		//packageServer.package(&sendMessage);
		////��������
		//serverSocket.socketSend(&sendMessage, 2048);
		//DHCPFinish = packageServer.getState();
		////if (DHCPFinish)//��������������ô�����ö�ʱ��
		////{
		////	clock.set(0, 1, 0);
		////	clock.run();//����ACK������ʱ��
		////}
		//closesocket(sClient);

	
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
