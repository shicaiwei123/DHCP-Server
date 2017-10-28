#pragma once
#include"DHCPPackageBasic.h"


class DHCPPackageServer :public DHCPPackageBasic
{
public:
	DHCPPackageServer(DHCPMessageStuct *Meassage);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
private:
	DHCPMessageStuct *meassageRecv;

};
