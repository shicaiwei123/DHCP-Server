#pragma once
#include"DHCPPackageBasic.h"
#include "DataManage.h"


class DHCPPackageServer :public DHCPPackageBasic
{
public:
	DHCPPackageServer(DHCPMessageStuct *Meassage);
	void begin();
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
	int IPDistribution(DHCPMessageStuct *Meassage);
	int addOption1(DHCPMessageStuct *Meassage, int MeassageType); //掩码
	int addOption3(DHCPMessageStuct *Meassage, int MeassageType); //网关
	int addOption51(DHCPMessageStuct *Meassage, int MeassageType);//租借时间
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);//报文类型


	void package();
	bool getState();
private:
	DHCPMessageStuct recvMessage;
	DHCPMessageStuct *testMessage;
	DHCPMessageStuct tempMessage;
	bool DHCPFinish;                 //判断是否完成配置。
	DataManege serverData;
};
