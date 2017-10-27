#pragma once
#include "DHCPPackageBasic.h"
class DHCPPackageClient :public DHCPPackageBasic
{
public:
	DHCPPackageClient(DHCPMessageStuct *Meassage, int MeassageType);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);
	//ÖØÔØº¯Êı£¬·â×°
	void package();
	void addOption53();
};


