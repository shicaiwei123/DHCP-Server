#pragma once
#include"DHCPPackageBasic.h"


class DHCPPackageServer :public DHCPPackageBasic
{
public:
	DHCPPackageServer(DHCPMessageStuct *Meassage);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
	int IPDistribution(DHCPMessageStuct *Meassage);
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);
	void package();
private:
	DHCPMessageStuct recvMessage;

};
