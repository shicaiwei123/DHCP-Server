
//#include <cstdio>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string.h>
//#include "stdafx.h"
#include <memory.h>
#include "SocketServer.h"
#pragma comment(lib,"ws2_32.lib")
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP

enum dhcp_msg_type {
	DHCP_DISCOVER = 1,
	DHCP_OFFER = 2,
	DHCP_REQUEST = 3,
	DHCP_DECLINE = 4,
	DHCP_ACK = 5,
	DHCP_NAK = 6,
	DHCP_RELEASE = 7,
	DHCP_INFORM = 8,
	DHCP_IACK = 9,
};

enum op_types {
	BOOTREQUEST = 1,
	BOOTREPLY = 2,
};

enum hardware_address_types {
	ETHERNET = 0x01,
	ETHERNET_LEN = 0x06,
};

typedef struct DHCPMsg
{
	uint8_t op;      // message op code, message type
	uint8_t htype;   // hardware address type
	uint8_t hlen;    // hardware address length
	uint8_t hops;    // incremented by relay agents

	uint32_t xid;    // transaction ID

	uint16_t secs;   // seconds since address acquisition or renewal
	uint16_t flags;  // flags

	uint32_t ciaddr; // client IP address
	uint32_t yiaddr; // 'your' client IP address
	uint32_t siaddr; // IP address of the next server to use in bootstrap
	uint32_t giaddr; // relay agent IP address

	uint8_t chaddr[16]; // client hardware address

	uint8_t sname[64]; // server host name

	uint8_t file[128]; // boot file name

	uint32_t dhcp_magic;
}DHCPMsg;

typedef struct DHCPOption
{
	char DHCPMeassageTyrp[4];
	char subnetMask[4];
	char routerAddress[4];
	char addressLeaseTime[4];
	char DNSServer[4];
	char broadcastAdress[4];



}DHCPOption;

 typedef struct DHCPMessage {
	DHCPMsg hdr;

	//dhcp_option_list list[10];
	//uint8_t option[256];
	DHCPOption option;

}DHCPMessage;

 typedef struct send_info
 {
	 char info_from[20]; //发送者ID
	 char info_to[20]; //接收者ID
	 char info_content[256]; //消息主体 
	 int info_length; //发送的消息主体的长度

 }recv_info;




int main(int argc, char* argv[])
{
//	DHCPMessage Packet;
//	DHCPMessage *DHCPPacket = &Packet;
////	memset(DHCPPacket, 0, sizeof(struct DHCPMessage));
//	DHCPPacket->hdr.xid = 0xaaaaaaaa;
//	DHCPPacket->hdr.htype = ETHERNET;
//	DHCPPacket->hdr.hlen = ETHERNET_LEN;
//	DHCPPacket->hdr.hops = 0;
//	DHCPPacket->hdr.ciaddr = 0;
//	DHCPPacket->hdr.yiaddr = 0;
//	DHCPPacket->hdr.flags = 0x0080;
//	DHCPPacket->hdr.secs = 0x0000;
//	DHCPPacket->hdr.siaddr = 0x00000000;
//	DHCPPacket->hdr.giaddr = 0;
//	//DHCPPacket->hdr.chaddr = 0;
//	//GetLocalMacAddr(DHCPPacket->hdr.chaddr);
//	DHCPPacket->hdr.dhcp_magic = 0x63538263;
//	DHCPPacket->hdr.op = BOOTREQUEST;

	recv_info info1;

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
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[1024];
	while (true)
	{
		printf("等待连接...\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
		memset(revData, 0, 1024);     //清空接收缓存
		//接收数据
		int ret = recv(sClient, revData, 1024, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
			//memcpy(&info1, revData, sizeof(revData));//把接收到的信息转换成结构体
			//printf("%s\n", info1.info_from);
			//printf("%s\n", info1.info_to);
			//printf("%s\n", info1.info_content);
			//printf("%d\n", info1.info_length);
		}

		//发送数据
		char * sendData = "你好，TCP客户端！\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
