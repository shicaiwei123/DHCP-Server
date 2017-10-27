
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
	// char info_from[20]; //������ID
	// char info_to[20]; //������ID
	// char info_content[256]; //��Ϣ���� 
	// int info_length; //���͵���Ϣ����ĳ���

 //}recv_info;




int main(int argc, char* argv[])
{
	DHCPMessageStuct message;

	DHCPMessageStuct *DHCPMessage = &message;
	memset(DHCPMessage, 0, sizeof(DHCPMessage));
	memset(&messageTemp, 0, sizeof(messageTemp));
	DHCPPackageServer serverPackage(DHCPMessage,DHCP_OFFER);
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
	char revData[4096];
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
		memset(revData, 0, sizeof(revData));     //��ս��ջ���
		//��������
		int ret = recv(sClient, revData, sizeof(revData), 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			//printf(revData);
			memcpy(&message, revData, sizeof(revData));//�ѽ��յ�����Ϣת���ɽṹ��
			messageTemp = message;
			serverPackage.analysis(&messageTemp);
		}

		//��������
		char * sendData = "��ã�TCP�ͻ��ˣ�\n";
		send(sClient, sendData, sizeof(sendData), 0);
		closesocket(sClient);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
