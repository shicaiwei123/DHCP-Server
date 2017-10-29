#pragma once
#include "DHCPPackageBasic.h"
class DHCPPackageClient :public DHCPPackageBasic
{
public:
	DHCPPackageClient(DHCPMessageStuct *Meassage);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
	bool getState();
	//重载函数，封装
	void package();
	void addOption53();
	

private:
	DHCPMessageStuct recvMessage;
	bool DHCPFinish;                 //判断是否完成配置。
};


