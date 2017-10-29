#pragma once
#include"DHCPPackageBasic.h"


class DHCPPackageServer :public DHCPPackageBasic
{
public:
	DHCPPackageServer(DHCPMessageStuct *Meassage);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
	int IPDistribution(DHCPMessageStuct *Meassage);
	int addOption1(DHCPMessageStuct *Meassage, int MeassageType); //����
	int addOption3(DHCPMessageStuct *Meassage, int MeassageType); //����
	int addOption51(DHCPMessageStuct *Meassage, int MeassageType);//���ʱ��
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);//��������


	void package();
	bool getState();
private:
	DHCPMessageStuct recvMessage;
	DHCPMessageStuct *testMessage;
	bool DHCPFinish;                 //�ж��Ƿ�������á�

};
