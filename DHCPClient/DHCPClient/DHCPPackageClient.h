#pragma once
#include "DHCPPackageBasic.h"
/*�ͻ��˱��Ĵ�����*/
//��Ͽͻ������󣬻��ڱ��Ĵ������������һЩ����������
//��װ��ѡ���еı�������
//���ķ�װ��ѡ���ṩ�����ֽӿڣ�������Ҫ����ָ���������͵�����
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


