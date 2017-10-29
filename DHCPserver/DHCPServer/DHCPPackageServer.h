#pragma once
#include"DHCPPackageBasic.h"
#include "DataManage.h"


class DHCPPackageServer :public DHCPPackageBasic
{
public:
	DHCPPackageServer(DHCPMessageStuct *Meassage);
	void begin();
//	int package(DHCPMessageStuct *Meassage, int MeassageType);//���Ƿ�����Ҳ����Ҫ������������
	int analysis(DHCPMessageStuct *Meassage);
	int addOption1(DHCPMessageStuct *Meassage, int MeassageType); //����
	int addOption3(DHCPMessageStuct *Meassage, int MeassageType); //����
	int addOption51(DHCPMessageStuct *Meassage, int MeassageType);//���ʱ��
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);//��������
	int package(DHCPMessageStuct *Message);//�������
	bool getState();//��ȡ����״̬���ж��Ƿ����
private:
	DHCPMessageStuct recvMessage;
	bool DHCPFinish;                 //�ж��Ƿ�������á�
	DataManege serverData;
	Address IPBuf;           //IP��ַ���棬������ʱ������Ͳ�ȷ��ʱ���ظ����ĵ�IP��ַѡ�����⡣
	int IPDistribution(DHCPMessageStuct *Meassage);
};
