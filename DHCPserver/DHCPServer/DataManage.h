#pragma once
#include"DHCPDataStruct.h"

class DataManege
{
public:
	DataManege();
	void begin();//当需要使用内部配置数据的时候调用此函数。
	void importData(IPManage *IPData);//从外部导入数据
	int readIPPool(Address *ip);//获取IP地址
private:
	IPManage *IPPool;
	IPManage localIPPool[10];
	bool flag;//是否使用外部数据true是，false否

};