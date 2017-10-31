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
	StaticIPManege* getIPdata();
private:
	DynamicIPManage *IPPool;
	DynamicIPManage dynamicIPPool[10];
	StaticIPManege staticIPPool[10];
	bool flag;//�Ƿ�ʹ���ⲿ����true�ǣ�false��

};