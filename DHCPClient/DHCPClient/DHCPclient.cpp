//#include "stdafx.h"
#include <STDIO.H>
#include "SocketClient.h"
#include "DHCPPackageClient.h"
#pragma comment(lib,"netapi32.lib")    //连接Netapi32.lib库，MAC获取中用到了NetApi32.DLL的功能  
#pragma comment(lib,"ws2_32.lib")
#include <iostream>


#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP

//全局变量，缓存收到的报文数据。
DHCPMessageStuct measseageTemp;


const char ip[] = {"127.0.0.1" };

//#define structTest

//结构体传输测试
#ifdef structTest
typedef struct send_info
{
	char info_from[20]; //发送者ID
	char info_to[20]; //接收者ID
	char info_content[256]; //消息主体 
	int info_length; //发送的消息主体的长度

}send_info;
#endif // structTest



int main(int argc, char* argv[])
{
	char sendData[8192];
	char recvData[8192];
	DHCPMessageStuct sendMessage;
	DHCPMessageStuct recvMessage;
	DHCPMessageStuct tempMessage;
	memset(&sendMessage, 0, sizeof(sendMessage));
	DHCPPackageClient clientPacket(&sendMessage, DHCP_DISCOVER);
	clientPacket.package();
	memcpy(sendData, &sendMessage, sizeof(sendMessage)); //结构体转换成字符串
	socketClient socketClinet;
	socketClinet.begin();
	socketClinet.socketCreate(TCP);
	socketClinet.socketConnect(ip, 8888);

#ifdef structTest
	send_info info1 = {"client","server","你好啊，李银河",15}; //定义结构体变量
	send_info info2;
	memset(send_buf, 0, 1024);//清空发送缓存，不清空的话可能导致接收时产生乱码，//或者如果本次发送的内容少于上次的话，snd_buf中会包含有上次的内容 
	printf("%s\n", info1.info_from);
	printf("%s\n", info1.info_to);
	printf("%s\n", info1.info_content);
	printf("%d\n", info1.info_length);
	memcpy(send_buf, &info1, sizeof(info1)); //结构体转换成字符串
	//数据转换的测试
	//memcpy(&info2, send_buf, sizeof(send_buf)); //结构体转换成字符串	

	//printf("转换之后：\n");
	//printf("%s\n", info2.info_from);
	//printf("%s\n", info2.info_to);
	//printf("%s\n", info2.info_content);
	//printf("%d\n", info2.info_length);
#endif // structTest

	SOCKET sclient = socketClinet.socketGet();
	send(sclient, sendData, sizeof(sendData), 0);
	//char * sendData = "你好,TCP服务端，我是客户端!\n";
	//send(sclient, sendData, strlen(sendData), 0);


	int ret = recv(sclient, recvData, sizeof(recvData), 0);
	if (ret > 0)
	{
		//recvData[ret] = 0x00;
		//printf(recvData);
		memcpy(&recvMessage, recvData, sizeof(recvData));//把接收到的信息转换成结构体
		tempMessage = recvMessage;
		clientPacket.analysis(&tempMessage);
	}
	closesocket(sclient);
	WSACleanup();
	return 0;
}