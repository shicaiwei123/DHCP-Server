
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
	 char info_from[20]; //������ID
	 char info_to[20]; //������ID
	 char info_content[256]; //��Ϣ���� 
	 int info_length; //���͵���Ϣ����ĳ���

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
	clock.set(0, 1, 0);//��ʼ����ʱ��Ϊ1����
	memcpy(VerifictionDataServer.question, "ABCDEF", 7);
	memcpy(VerifictionDataServer.answer, "ABCDEF", 7);
	int VerFlag = 0;
	int err;
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
	//sockaddr_in remoteAddr;
	//int nAddrlen = sizeof(remoteAddr);
	
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
	
			//��������
		recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		packageServer.analysis(&recvMessage);
		packageServer.package(&sendMessage);
			//��������
		serverSocket.socketSend(&sendMessage,2048);
		DHCPFinish = packageServer.getState();
		//if (DHCPFinish)//��������������ô�����ö�ʱ��
		//{
		//	clock.set(0, 1, 0);
		//	clock.run();//����ACK������ʱ��
		//	break;
		//}

		//��������

		recvMessage = serverSocket.socketRecv(recvData, sizeof(recvData));
		packageServer.analysis(&recvMessage);
		memset(&recvMessage, 0, sizeof(DHCPMessageStuct));
		packageServer.package(&sendMessage);
		while (!VerFlag)
		{
			//��������
			VerifictionServer.sendQuestiooon(slisten, VerifictionDataServer.question, VerifictionDataServer.answer);

			//������֤
			VerFlag = VerifictionServer.ckeck(slisten);
		}

		serverSocket.socketSend(&sendMessage, 2048);
		DHCPFinish = packageServer.getState();
		//if (DHCPFinish)//��������������ô�����ö�ʱ��
		//{
		//	clock.set(0, 1, 0);
		//	clock.run();//����ACK������ʱ��
		//}
		closesocket(sClient);

	
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
