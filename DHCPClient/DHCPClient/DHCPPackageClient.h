#pragma once
#include "DHCPPackageBasic.h"
class DHCPPackageClient :public DHCPPackageBasic
{
public:
	DHCPPackageClient(DHCPMessageStuct *Meassage, int MeassageType);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
	//���غ�������װ
	void package();
private:
	DHCPMessageStuct *meassageRecv;
};


