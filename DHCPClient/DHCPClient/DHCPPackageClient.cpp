#include "DHCPPackageClient.h"

DHCPPackageClient::DHCPPackageClient(DHCPMessageStuct *Meassage):DHCPPackageBasic(Meassage)
{
	meassageType = DHCP_DISCOVER;
	memset(&recvMessage, 0, sizeof(recvMessage));
	DHCPFinish = false;
}

int DHCPPackageClient::package(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	switch (MeassageType)
	{
	case DHCP_DISCOVER:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.xid = 0xaaaaaaaa;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.ciaddr.address = 0;
		packet->hdr.yiaddr.address = 0;
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		MACAGet((char*)packet->hdr.chaddr);
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		packet->hdr.op = BOOTREQUEST;
		addOption53(packet, MeassageType);
		break;

	case DHCP_REQUEST:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.op = BOOTREQUEST;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.xid = 0x1111111a;
		packet->hdr.ciaddr.address=0;
		packet->hdr.yiaddr.address=0;
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		MACAGet((char*)packet->hdr.chaddr);
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		addOption53(packet, MeassageType);
		break;

	default:
		break;
	};
	return 0;
}

int DHCPPackageClient::addOption53(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	packet->option.DHCPMeassageType = MeassageType;
	return 0;

}

void DHCPPackageClient::package()
{

	package(meassage, meassageType);
}

void DHCPPackageClient::addOption53()
{
	addOption53(meassage, meassageType);
}

int DHCPPackageClient::analysis(DHCPMessageStuct *Meassage)
{
	recvMessage = *Meassage;
	cout << "报文类型是：";
	printf("%d\n", Meassage->option.DHCPMeassageType);
	cout << "可用IP地址是："
		<< (int)Meassage->hdr.yiaddr.seg[3]  << "."
		<< (int)Meassage->hdr.yiaddr.seg[2]<< "."
		<< (int)Meassage->hdr.yiaddr.seg[1] << "."
		<< (int)Meassage->hdr.yiaddr.seg[0] << "."
		<< endl;
	if (recvMessage.option.DHCPMeassageType == DHCP_ACK)
		DHCPFinish = true;
	switch (recvMessage.option.DHCPMeassageType)
	{
	case DHCP_OFFER:
		meassageType = DHCP_REQUEST;
		break;
	default:
		break;
	}

	return 0;
}

bool DHCPPackageClient::getState()
{
	return DHCPFinish;
}
