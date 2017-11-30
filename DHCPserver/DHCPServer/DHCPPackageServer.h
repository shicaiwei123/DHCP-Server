#pragma once
#include"DHCPPackageBasic.h"
#include "DataManage.h"


class DHCPPackageServer :public DHCPPackageBasic
{
public:
	DHCPPackageServer(DHCPMessageStuct *Meassage);
	void begin();
	void setTime(uint8_t *Time);   //�趨��Լʱ��
//	void begin(DynamicIPManage *DynamicIPPool, StaticIPManege *StaticIPPool);
//	int package(DHCPMessageStuct *Meassage, int MeassageType);//���Ƿ�����Ҳ����Ҫ������������
	int analysis(DHCPMessageStuct *Meassage);
	int addOption1(DHCPMessageStuct *Meassage); //����
	int addOption3(DHCPMessageStuct *Meassage); //����
	int addOption51(DHCPMessageStuct *Meassage, uint8_t *Time);//���ʱ��
	int addOption53(DHCPMessageStuct *Meassage);//��������
	int package(DHCPMessageStuct *Message);//�������
	bool getState();//��ȡ����״̬���ж��Ƿ����
	DHCPMessageStuct getRecvMessage();
	int setData(DataManege *ServerData);  //�������ݹ�����
	void reflash();//ˢ��IP״̬


private:
	DHCPMessageStuct recvMessage;
	bool DHCPFinish;                 //�ж��Ƿ�������á�
	DataManege *serverData;
	Address IPBuf;           //IP��ַ���棬������ʱ������Ͳ�ȷ��ʱ���ظ����ĵ�IP��ַѡ�����⡣
	int IPDistribution(DHCPMessageStuct *Meassage);
	uint8_t time[3];
};
