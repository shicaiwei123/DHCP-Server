//#include "stdafx.h"
#include <STDIO.H>
#include "SocketClient.h"
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

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




int main(int argc, char* argv[])
{
	char send_buf[1024];
	socketClient socketClinet;
	socketClinet.begin();
	socketClinet.socketCreate(TCP);
	socketClinet.socketConnect(ip, 8888);

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

	SOCKET sclient = socketClinet.socketGet();
	char * sendData = "���,TCP����ˣ����ǿͻ���!\n";
	send(sclient, sendData, strlen(sendData), 0);

	char recData[1024];
	int ret = recv(sclient, recData, 1024, 0);
	if (ret > 0)
	{
		recData[ret] = 0x00;
		printf(recData);

	
	}
	closesocket(sclient);
	WSACleanup();
	return 0;
}