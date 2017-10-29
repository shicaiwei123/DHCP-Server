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
	memset(&clientMessage, 0, sizeof(clientMessage));//初始化客户端网络数据

	DHCPPackageClient packageClient(&sendMessage);

	socketClient socketClinet;
	socketClinet.begin();
	socketClinet.socketCreate(TCP);
	socketClinet.socketConnect(ip, 8888);
	SOCKET sclient = socketClinet.socketGet();
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
	
		//char * sendData = "你好,TCP服务端，我是客户端!\n";
		packageClient.package(&sendMessage,DHCP_DISCOVER);
		memcpy(sendData, &sendMessage, sizeof(DHCPMessageStuct)); //结构体转换成字符串
		send(sclient, sendData, 2048, 0);    //方便兼容长度，字符串和后面数据的求长度函数不一样


		int ret = recv(sclient, recvData, 4096, 0);
		if (ret > 0)
		{
			//recvData[ret] = 0x00;
			//printf(recvData);
			memcpy(&recvMessage, recvData, sizeof(recvMessage)); //结构体转换成字符串
			tempMessage = recvMessage;
			packageClient.analysis(&tempMessage);
	
		}

		//Request
		packageClient.package();
		memcpy(sendData, &sendMessage, sizeof(DHCPMessageStuct)); //结构体转换成字符串
		send(sclient, sendData, 2048, 0);    //方便兼容长度，字符串和后面数据的求长度函数不一样


		ret = recv(sclient, recvData, 4096, 0);
		if (ret > 0)
		{
			//recvData[ret] = 0x00;
			//printf(recvData);
			memcpy(&recvMessage, recvData, sizeof(recvMessage)); //结构体转换成字符串
			tempMessage = recvMessage;
			packageClient.analysis(&tempMessage);

		}
		dataManege.dataFresh(&recvMessage);
		clientData = dataManege.getClientData();
	DHCPFinish = packageClient.getState();
	closesocket(sclient);
	WSACleanup();
	return 0;
}