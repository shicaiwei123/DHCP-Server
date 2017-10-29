#include "DHCPPackageServer.h"

DHCPPackageServer::DHCPPackageServer(DHCPMessageStuct *Meassage):DHCPPackageBasic(Meassage)
{
	testMessage = Meassage;
	
}

void DHCPPackageServer::begin()
{
	serverData.begin();
	meassageType = DHCP_OFFER;
	memset(&recvMessage, 0, sizeof(recvMessage));
}
int DHCPPackageServer::package(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	switch (MeassageType)
	{
	case DHCP_OFFER:
	//	memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.op = BOOTREPLY;
		packet->hdr.xid = recvMessage.hdr.xid;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.ciaddr.address = 0;
		IPDistribution(packet);
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		memcpy(packet->hdr.chaddr, &recvMessage.hdr.chaddr, sizeof(recvMessage.hdr.chaddr)); //数组数据copy。
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		addOption1(packet, MeassageType);
		addOption3(packet, MeassageType);
		addOption51(packet, MeassageType);
		addOption53(packet, MeassageType);
		break;

	case DHCP_ACK:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.op = BOOTREPLY;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.xid = recvMessage.hdr.xid;;
		packet->hdr.ciaddr.address = 0;
		packet->hdr.yiaddr.address = 0;
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		memcpy(packet->hdr.chaddr, &recvMessage.hdr.chaddr, sizeof(recvMessage.hdr.chaddr)); //数组数据copy。
		*packet->hdr.chaddr = *recvMessage.hdr.chaddr;   //取数组内容
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		addOption1(packet, MeassageType);
		addOption3(packet, MeassageType);
		addOption51(packet, MeassageType);
		addOption53(packet, MeassageType);
		break;

	default:
		break;
	}
	return 0;
}

int DHCPPackageServer::analysis(DHCPMessageStuct *Meassage)
{
	recvMessage = *Meassage;
	cout << "报文类型是：";
	printf("%d\n", Meassage->option.DHCPMeassageType);
	cout << "客户端MAC地址是：" << Meassage->hdr.chaddr<<endl;
	switch (Meassage->option.DHCPMeassageType)  //修改状态
	{
	case DHCP_DISCOVER:
		meassageType = DHCP_OFFER;
		break;
	case DHCP_REQUEST:
		meassageType = DHCP_ACK;
		break;
	default:
		break;
	}
	return 0;
}
int DHCPPackageServer::addOption1(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	packet->option.subnetMask = Meassage->option.subnetMask;
	return 0;

}

int DHCPPackageServer::addOption3(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	packet->option.routerAddress = Meassage->option.routerAddress;
	return 0;

}

int DHCPPackageServer::addOption51(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	packet->option.addressLeaseTime = Meassage->option.addressLeaseTime;
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
	DHCPMessageStuct *packet = testMessage;
	switch (meassageType)
	{
	case DHCP_OFFER:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.op = BOOTREPLY;
		packet->hdr.xid = recvMessage.hdr.xid;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.ciaddr.address = 0;
		IPDistribution(packet);
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		memcpy(packet->hdr.chaddr, &recvMessage.hdr.chaddr, sizeof(recvMessage.hdr.chaddr)); //数组数据copy。
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		addOption53(packet, meassageType);
		tempMessage = *packet;
		break;

	case DHCP_ACK:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		*packet = tempMessage;
		packet->option.DHCPMeassageType = meassageType;    //因为OFFER和ACK报文只是相差了一个类型
		//packet->hdr.op = BOOTREPLY;
		//packet->hdr.htype = ETHERNET;
		//packet->hdr.hlen = ETHERNET_LEN;
		//packet->hdr.hops = 0;
		//packet->hdr.xid = recvMessage.hdr.xid;;
		//packet->hdr.ciaddr.address = 0;
		//packet->hdr.yiaddr.address=
		//packet->hdr.flags = 0x0080;
		//packet->hdr.secs = 0x0000;
		//packet->hdr.siaddr.address = 0x00000000;
		//packet->hdr.giaddr.address = 0;
		//memcpy(packet->hdr.chaddr, &recvMessage.hdr.chaddr, sizeof(recvMessage.hdr.chaddr)); //数组数据copy。
		//*packet->hdr.chaddr = *recvMessage.hdr.chaddr;   //取数组内容
		//memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		//memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		//packet->hdr.dhcp_magic = 0x63538263;
		addOption53(packet, meassageType);
		DHCPFinish = true;
		break;

	default:
		break;
	}

}

int DHCPPackageServer::IPDistribution(DHCPMessageStuct *Meassage)
{
	serverData.readIPPool(&Meassage->hdr.yiaddr);
	//Meassage->hdr.yiaddr.seg[3] = 192;
	//Meassage->hdr.yiaddr.seg[2] = 168;
	//Meassage->hdr.yiaddr.seg[1] = 1;
	//Meassage->hdr.yiaddr.seg[0] = 0;
	Meassage->option.addressLeaseTime = 12;
	Meassage->option.subnetMask.seg[3] = 255;Meassage->option.subnetMask.seg[2] = 255;
	Meassage->option.subnetMask.seg[1] = 255;Meassage->option.subnetMask.seg[0] = 0;
	Meassage->option.routerAddress.seg[3] = 192;Meassage->option.routerAddress.seg[2] = 168;
	Meassage->option.routerAddress.seg[1] = 1; Meassage->option.routerAddress.seg[0] = 1;
	return 0;

}

bool DHCPPackageServer::getState()
{
	return DHCPFinish;
}
