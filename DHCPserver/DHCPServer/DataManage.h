#pragma once
#include"DHCPDataStruct.h"

class DataManege
{
public:
	DataManege();
	void begin();//����Ҫʹ���ڲ��������ݵ�ʱ����ô˺�����
	void importData(DynamicIPManage *IPData);//���ⲿ��������
	int readDynamicIPPool(Address *ip);//��ȡIP��ַ
	int readStaticIPPool(Address *Ip,char *Mac);//��ȡIP��ַ
	void reflash(Address *Ip, char *Mac);//���¾�̬��
	void reflash(char *Mac); //ˢ��IP��ַ��״̬
	StaticIPManege* getIPdata();
private:
	int counter; //��ַ������
	 DynamicIPManage *IPPool;
	 DynamicIPManage dynamicIPPool[10];
	 StaticIPManege staticIPPool[20];
	bool flag;//�Ƿ�ʹ���ⲿ����true�ǣ�false��

};