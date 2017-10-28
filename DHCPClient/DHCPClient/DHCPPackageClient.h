#pragma once
#include "DHCPPackageBasic.h"
class DHCPPackageClient :public DHCPPackageBasic
{
public:
	DHCPPackageClient(DHCPMessageStuct *Meassage);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
	//ÖØÔØº¯Êý£¬·â×°
	void package(DHCPMessageStuct *Meassage);
	void addOption53();

private:
	DHCPMessageStuct *recvMessage;
};


