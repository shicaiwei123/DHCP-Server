#include "DHCPPackageServer.h"

DHCPPackageServer::DHCPPackageServer(DHCPMessageStuct *Meassage)
{
	meassage = Meassage;
	meassageType = DHCP_OFFER;
}

int DHCPPackageServer::package(DHCPMessageStuct *Meassage, int MeassageType)
{
	return 0;
}

int DHCPPackageServer::analysis(DHCPMessageStuct *Meassage)
{
	meassageRecv = Meassage;
	cout << "���������ǣ�";
	printf("%d", meassageRecv->option.DHCPMeassageType);
	cout << "�ͻ���MAC��ַ�ǣ�" << meassageRecv->hdr.chaddr<<endl;
	return 0;
}