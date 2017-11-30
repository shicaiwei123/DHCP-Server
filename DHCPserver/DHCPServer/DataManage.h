#pragma once
#include"DHCPDataStruct.h"

class DataManege
{
public:
	DataManege();
	void begin();//当需要使用内部配置数据的时候调用此函数。
	void importData(DynamicIPManage *IPData);//从外部导入数据
	int readDynamicIPPool(Address *ip);//获取IP地址
	int readStaticIPPool(Address *Ip,char *Mac);//获取IP地址
	void reflash(Address *Ip, char *Mac);//更新静态表
	void reflash(char *Mac); //刷新IP地址的状态
	StaticIPManege* getIPdata();
private:
	int counter; //地址计数器
	 DynamicIPManage *IPPool;
	 DynamicIPManage dynamicIPPool[10];
	 StaticIPManege staticIPPool[20];
	bool flag;//是否使用外部数据true是，false否

};