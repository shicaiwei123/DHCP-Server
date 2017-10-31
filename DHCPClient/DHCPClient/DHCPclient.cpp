//#include "stdafx.h"
#include <STDIO.H>
#include "SocketClient.h"
#include"DHCPPackageClient.h"
#include "DataManege.h"
#pragma comment(lib,"ws2_32.lib")


#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP
const char ip[] = {"127.0.0.1" };

//#define structTest

//�ṹ�崫�����
#ifdef structTest
typedef struct send_info
{
	char info_from[20]; //������ID
	char info_to[20]; //������ID
	char info_content[256]; //��Ϣ���� 
	int info_length; //���͵���Ϣ����ĳ���

}send_info;
#endif // structTest
DHCPMessageStuct clientMessage;



int main(int argc, char* argv[])
{
	char sendData[1024];
	char recvData[4096];
	bool DHCPFinish = false;
	ClientData clientData;
	DHCPMessageStuct sendMessage;
	DHCPMessageStuct recvMessage;
	DHCPMessageStuct tempMessage;
	DataManege dataManege;
	memset(&clientMessage, 0, sizeof(clientMessage));//��ʼ���ͻ�����������

	DHCPPackageClient packageClient(&sendMessage);

	socketClient socketClinet;
	socketClinet.begin();
	socketClinet.socketCreate(TCP);
	socketClinet.socketConnect(ip, 8888);
	SOCKET sclient = socketClinet.socketGet();
#ifdef structTest
		send_info info1 = {"client","server","��ð���������",15}; //����ṹ�����
	send_info info2;
	memset(send_buf, 0, 1024);//��շ��ͻ��棬����յĻ����ܵ��½���ʱ�������룬//����������η��͵����������ϴεĻ���snd_buf�л�������ϴε����� 
	printf("%s\n", info1.info_from);
	printf("%s\n", info1.info_to);
	printf("%s\n", info1.info_content);
	printf("%d\n", info1.info_length);
	memcpy(send_buf, &info1, sizeof(info1)); //�ṹ��ת�����ַ���
	//����ת���Ĳ���
	//memcpy(&info2, send_buf, sizeof(send_buf)); //�ṹ��ת�����ַ���	

	//printf("ת��֮��\n");
	//printf("%s\n", info2.info_from);
	//printf("%s\n", info2.info_to);
	//printf("%s\n", info2.info_content);
	//printf("%d\n", info2.info_length);
#endif // structTest
	//DISCOVER--OFFER
		packageClient.package(&sendMessage,DHCP_DISCOVER);
		socketClinet.socketSend(&sendMessage, 2048);
		recvMessage=socketClinet.socketRecv(recvData, 4096);
		tempMessage = recvMessage;
		packageClient.analysis(&tempMessage);
	//REQUEST--ACK
flag1:	packageClient.package();
		socketClinet.socketSend(&sendMessage, 2048);
		recvMessage = socketClinet.socketRecv(recvData, 4096);
		tempMessage = recvMessage;
		packageClient.analysis(&tempMessage);
	//״̬����
		dataManege.dataFresh(&recvMessage);
		clientData = dataManege.getClientData();
		DHCPFinish = packageClient.getState();
		if (dataManege.startCounter())
			goto flag1;
	closesocket(sclient);
	WSACleanup();
	return 0;
}