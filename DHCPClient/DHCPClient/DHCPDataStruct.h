#pragma once
#include <iostream>

union Address
{
	unsigned char seg[4]; //IP��ַ��4�ֽڣ����߿����޷����ַ�������ָ4����
	unsigned int address; //���߿���һ������

};

//�������ݽṹ
//DHCP�������ͱ�ʶ
enum DHCPMmsgType {
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
//DHCP����ѡ���ʶ
enum opTypes {
	BOOTREQUEST = 1,
	BOOTREPLY = 2,
};
//DHCP����������ַ��ʶ
enum hardwareAddressTypes {
	ETHERNET = 0x01,
	ETHERNET_LEN = 0x06,
};
//DHCP���ı��Ļ����ײ�
typedef struct DHCPMsg
{
	uint8_t op;      // message op code, message type
	uint8_t htype;   // hardware address type
	uint8_t hlen;    // hardware address length
	uint8_t hops;    // incremented by relay agents

	uint32_t xid;    // transaction ID

	uint16_t secs;   // seconds since address acquisition or renewal
	uint16_t flags;  // flags

	Address ciaddr; // client IP address
	Address yiaddr; // 'your' client IP address
	Address siaddr; // IP address of the next server to use in bootstrap
	Address giaddr; // relay agent IP address

	uint8_t chaddr[16]; // client hardware address

	uint8_t sname[64]; // server host name

	uint8_t file[128]; // boot file name

	uint32_t dhcp_magic;
}DHCPMsg;
//DHCP����ѡ��
typedef struct DHCPOption
{
	uint8_t DHCPMeassageType;
	Address subnetMask;
	Address routerAddress;
	uint8_t addressLeaseTime;
	Address DNSServer;
	Address broadcastAdress;



}DHCPOption;
//����DHCP�����ײ�
typedef struct DHCPMessage {
	DHCPMsg hdr;
	DHCPOption option;

	//dhcp_option_list list[10];
	//uint8_t option[256];

}DHCPMessageStuct;
