
//#include <cstdio>
#include <string.h>

#include <memory.h>
#include "SocketServer.h"
#include"DHCPPackageServer.h"
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

	char recvData[4096];
	char sendData[2048];
	DHCPMessageStuct sendMessage;
	DHCPMessageStuct recvMessage;
	DHCPMessageStuct tempMessage;
	DHCPPackageServer packageServer(&sendMessage);


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
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);

	while (true)
	{
		printf("�ȴ�����...\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));

		//��������
		memset(recvData, 0, strlen(recvData));     //��ս��ջ���
		int ret = recv(sClient, recvData, sizeof(recvData), 0);
		if (ret > 0)
		{
			//recvData[ret] = 0x00;
			//printf(recvData);
			memcpy(&recvMessage, recvData, sizeof(recvMessage)); //�ṹ��ת�����ַ���
			tempMessage = recvMessage;
			packageServer.analysis(&tempMessage);

		}

		//��������
		//char * sendData = "��ã�TCP�ͻ��ˣ�\n";
		packageServer.package(&sendMessage,DHCP_OFFER);
		memcpy(sendData, &sendMessage, sizeof(sendMessage)); //�ṹ��ת�����ַ���
		send(sClient, sendData, 2048, 0);
		closesocket(sClient);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
