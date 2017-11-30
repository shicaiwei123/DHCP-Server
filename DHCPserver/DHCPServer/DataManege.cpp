#include "DataManage.h"

DataManege::DataManege()
{
	flag = false;
	IPPool = NULL;
	memset(dynamicIPPool, 0, sizeof(DynamicIPManage));
	memset(staticIPPool, 0, sizeof(StaticIPManege));
	
}

void DataManege::begin()
{
	counter = sizeof(dynamicIPPool) / sizeof(DynamicIPManage);

	//192.168.1.3--192.168.1.12，动态IP池初始化
	for (int i = 0; i < sizeof(dynamicIPPool) / sizeof(DynamicIPManage); i++)
	{
		dynamicIPPool[i].ipAddress.seg[3] = 192;	dynamicIPPool[i].ipAddress.seg[2] = 168;
		dynamicIPPool[i].ipAddress.seg[1] = 1;   dynamicIPPool[i].ipAddress.seg[0] = 3 + i;
		dynamicIPPool[i].isFree = true;
	}
	//静态IP池初始化
	for (int i = 0; i < sizeof(dynamicIPPool) / sizeof(DynamicIPManage); i++)
	{
		staticIPPool[i].IPData.ipAddress.seg[3] = 192;
		staticIPPool[i].IPData.ipAddress.seg[2] = 168;
		staticIPPool[i].IPData.ipAddress.seg[1] = 1;
		staticIPPool[i].IPData.ipAddress.seg[0] = 20+i;
		staticIPPool[i].IPData.isFree = true;
	}

	memcpy(staticIPPool[0].MAC, "10-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[1].MAC, "20-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[2].MAC, "30-52-CB-61-90-2F", 18);
	memcpy(staticIPPool[3].MAC, "40-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[4].MAC, "50-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[5].MAC, "60-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[6].MAC, "70-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[7].MAC, "80-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[8].MAC, "90-52-CB-61-90-6F", 18);
	memcpy(staticIPPool[9].MAC, "30-12-CB-61-90-6F", 18);


}
void DataManege::reflash(Address *Ip, char *Mac)
{
	bool repeat = false;
	for (int i = 0; i < counter;i++)
	{
		int equel = 0;
		equel=strcmp((const char*)staticIPPool[counter].MAC, Mac);
		if (equel)//如果不相等相等
		{
			 repeat = true;
			break;

		}
	}

	if (repeat)
	{
		counter = counter + 1;
		staticIPPool[counter].IPData.ipAddress.address = Ip->address;
		memcpy(staticIPPool[counter].MAC, Mac, 18);
		staticIPPool[counter].IPData.isFree = true;
	}

}

void DataManege::reflash(char *Mac)
{
	for (int i = 0; i < counter; i++)
		if (!strcmp((const char*)staticIPPool[counter].MAC, Mac))//如果相等
		{
			staticIPPool[i].IPData.isFree = true;
		}
}
//DataManege::dynamicIPPool[1].isFree = false;
//void DataManege::getData(DynamicIPManage *DynamicIPPool, StaticIPManege *StaticIPPool)
//{
//	DynamicIPPool = this->dynamicIPPool;
//	StaticIPPool = this->staticIPPool;
//}
//void DataManege::importData(DynamicIPManage *DynamicIPPool, StaticIPManege *StaticIPPool)
//{
//	dynamicIPPool = DynamicIPPool;
//	staticIPPool = StaticIPPool;
//
//}
int DataManege::readDynamicIPPool(Address *ip)
{
	int j=0;
	for (int i = 0; i < sizeof(dynamicIPPool) / sizeof(DynamicIPManage);i++)
		if (dynamicIPPool[i].isFree)
		{
			memcpy(ip, &dynamicIPPool[i].ipAddress, sizeof(Address)); //数据赋值
			dynamicIPPool[i].isFree = false;
			j++;
			return 0;
		}
	if (!j)  //没有空闲IP
	{
		return -1;
	}
	return 0;
}

int DataManege::readStaticIPPool(Address *Ip, char *Mac)
{
		int flag = 0;
		for (int i = 0; i < sizeof(staticIPPool) / sizeof(StaticIPManege); i++)
		{
			flag = strcmp((char*)staticIPPool[i].MAC, Mac);
			if (!flag)//如果匹配到
			{
				Ip->address = staticIPPool[i].IPData.ipAddress.address;
				return 0;
			}
		
		}
		return -1;//没有匹配返回-1；
}

StaticIPManege* DataManege::getIPdata()
{
	return staticIPPool;
}
