#pragma once
#include"DHCPDataStruct.h"

class DataManege
{
public:
	DataManege();
	void begin();//����Ҫʹ���ڲ��������ݵ�ʱ����ô˺�����
	void importData(IPManage *IPData);//���ⲿ��������
	int readIPPool(Address *ip);//��ȡIP��ַ
private:
	IPManage *IPPool;
	IPManage localIPPool[10];
	bool flag;//�Ƿ�ʹ���ⲿ����true�ǣ�false��

};