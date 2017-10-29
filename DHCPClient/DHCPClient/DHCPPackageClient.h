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
	//���غ�������װ
	void package();
	void addOption53();
	

private:
	DHCPMessageStuct recvMessage;
	bool DHCPFinish;                 //�ж��Ƿ�������á�
};


