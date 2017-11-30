#include "DHCPPackageServer.h"

DHCPPackageServer::DHCPPackageServer(DHCPMessageStuct *Meassage):DHCPPackageBasic(Meassage)
{
	meassageType = DHCP_OFFER;
	memset(&recvMessage, 0, sizeof(recvMessage));
	memset(&IPBuf, 0, sizeof(IPBuf));
	DHCPFinish = false;
}

void DHCPPackageServer::begin()
{
	//serverData.begin();

	time[0] = 0;//时
	time[1] = 1;//分
	time[2] = 0;//秒

}

void DHCPPackageServer::setTime(uint8_t *Time)
{
	time[0] = *Time++;
	time[1] = *Time++;
	time[2] = *Time++;

}
//void DHCPPackageServer::begin(DynamicIPManage *DynamicIPPool, StaticIPManege *StaticIPPool)
//{
//	serverData.importData(DynamicIPPool, StaticIPPool);
//}


int DHCPPackageServer::setData(DataManege *ServerData)
{
	serverData = ServerData;
	return 0;
}
/*
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
*/
int DHCPPackageServer::analysis(DHCPMessageStuct *Meassage)
{
	recvMessage = *Meassage;
	cout << "报文类型是：";
	if (Meassage->option.DHCPMeassageType == 1)
		printf("DISCOVER\n");
	else if (Meassage->option.DHCPMeassageType == 3)
		printf("REQUEST\n");
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
int DHCPPackageServer::addOption1(DHCPMessageStuct *Meassage)
{
	//掩码
	Meassage->option.subnetMask.seg[3] = 255; Meassage->option.subnetMask.seg[2] = 255;
	Meassage->option.subnetMask.seg[1] = 255; Meassage->option.subnetMask.seg[0] = 0;
	return 0;

}

int DHCPPackageServer::addOption3(DHCPMessageStuct *Meassage)
{
	//网关
	Meassage->option.routerAddress.seg[3] = 192; Meassage->option.routerAddress.seg[2] = 168;
	Meassage->option.routerAddress.seg[1] = 1; Meassage->option.routerAddress.seg[0] = 1;
	return 0;

}

int DHCPPackageServer::addOption51(DHCPMessageStuct *Meassage, uint8_t *Time)
{
	DHCPMessageStuct *packet = Meassage;
	memcpy(packet->option.addressLeaseTime, Time, 3*sizeof(uint8_t));
	return 0;

}

int DHCPPackageServer::addOption53(DHCPMessageStuct *Meassage)
{
	DHCPMessageStuct *packet = Meassage;
	packet->option.DHCPMeassageType = meassageType;
	return 0;

}


int DHCPPackageServer::package(DHCPMessageStuct *Message)
{
	DHCPMessageStuct *packet = Message;
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
		addOption1(packet);
		addOption3(packet);
		addOption51(packet,time);
		addOption53(packet);
		IPBuf.address = packet->hdr.yiaddr.address;
		break;

	case DHCP_ACK:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->option.DHCPMeassageType = meassageType;    
		packet->hdr.op = BOOTREPLY;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.xid = recvMessage.hdr.xid;;
		packet->hdr.ciaddr.address = 0;
		IPDistribution(packet);
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		memcpy(packet->hdr.chaddr, &recvMessage.hdr.chaddr, sizeof(recvMessage.hdr.chaddr)); //数组数据copy。
		*packet->hdr.chaddr = *recvMessage.hdr.chaddr;   //取数组内容
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		addOption1(packet);
		addOption3(packet);
		addOption51(packet, time);
		addOption53(packet);
		DHCPFinish = true;
		break;

	default:
		break;
	}
	return 0;

}

int DHCPPackageServer::IPDistribution(DHCPMessageStuct *Meassage)
{
	int flag = 0;
	StaticIPManege *a = serverData->getIPdata();
	if (!IPBuf.address)    //如果IP缓存为空
	{
		flag = serverData->readStaticIPPool(&Meassage->hdr.yiaddr,(char*)(&recvMessage.hdr.chaddr));
		StaticIPManege *a = serverData->getIPdata();
		if (flag == -1)//静态表没有记录
			serverData->readDynamicIPPool(&Meassage->hdr.yiaddr);
	}

	else
	{
		Meassage->hdr.yiaddr.address = IPBuf.address;
		memset(&IPBuf, 0, sizeof(Address));
	}
	serverData->reflash(&Meassage->hdr.yiaddr, (char*)(&recvMessage.hdr.chaddr));
	return 0;

}

bool DHCPPackageServer::getState()
{
	return DHCPFinish;
}

DHCPMessageStuct DHCPPackageServer::getRecvMessage()
{
	return recvMessage;
}

void DHCPPackageServer::reflash()
{
	serverData->reflash((char*)(&recvMessage.hdr.chaddr));
}
