#include "DHCPPackageServer.h"

DHCPPackageServer::DHCPPackageServer(DHCPMessageStuct *Meassage, int MeassageType)
{
	meassage = Meassage;
	meassageType = MeassageType;
}

int DHCPPackageServer::package(DHCPMessageStuct *Meassage, int MeassageType)
{
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