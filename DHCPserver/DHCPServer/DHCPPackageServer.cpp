#include "DHCPPackageServer.h"

DHCPPackageServer::DHCPPackageServer(DHCPMessageStuct *Meassage, int MeassageType)
{
	meassage = Meassage;
	meassageType = MeassageType;
}

int DHCPPackageServer::package(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	switch (MeassageType)
	{
	case DHCP_OFFER:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.op = BOOTREPLY;
		packet->hdr.xid = meassageRecv->hdr.xid;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.ciaddr.address = 0;
        IPDistribution(packet);
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

	case DHCP_ACK:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.op = BOOTREPLY;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.xid = meassageRecv->hdr.xid;;
		packet->hdr.ciaddr.address = 0;
		packet->hdr.yiaddr.address = 0;
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		*packet->hdr.chaddr = *meassageRecv->hdr.chaddr;
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		addOption53(packet, MeassageType);
		break;

	default:
		break;
	}
	return 0;
}

int DHCPPackageServer::analysis(DHCPMessageStuct *Meassage)
{
	meassageRecv = Meassage;
	cout << "报文类型是：";
	printf("%d", meassageRecv->option.DHCPMeassageType);
	cout << "客户端MAC地址是：" << meassageRecv->hdr.chaddr<<endl;
	return 0;
}

int DHCPPackageServer::addOption53(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	packet->option.DHCPMeassageType = MeassageType;
	return 0;

}

void DHCPPackageServer::package()
{
	package(meassage, meassageType);
}

int DHCPPackageServer::IPDistribution(DHCPMessageStuct *Meassage)
{
	Meassage->hdr.yiaddr.seg[3] = 192;
	Meassage->hdr.yiaddr.seg[2] = 168;
	Meassage->hdr.yiaddr.seg[1] = 1;
	Meassage->hdr.yiaddr.seg[0] = 0;
	return 0;

}