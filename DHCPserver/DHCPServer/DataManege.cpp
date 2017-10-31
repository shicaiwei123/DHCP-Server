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
	//char mac1[] = "30-52-CB-61-90-6F";
	//char mac2[] = "10-52-CB-61-90-6F";
	//char mac3[] = "20-22-CB-61-90-6F";
	//char mac4[] = "40-52-EB-61-90-6F";
	//char mac5[] = "50-52-CB-41-90-6F";
	//char mac6[] = "60-52-CB-61-50-6F";
	//char mac7[] = "70-52-CB-61-90-7F";
	//char mac8[] = "30-52-CB-61-80-6F";
	//char mac9[] = "30-52-CB-91-90-6F";
	//char mac10[] = "30-52-CB-61-90-6F";

	//192.168.1.3--192.168.1.12，动态IP池初始化
	for (int i = 0; i < sizeof(dynamicIPPool)/sizeof(DynamicIPManage);i++)
	{
		dynamicIPPool[i].ipAddress.seg[3] = 192;	dynamicIPPool[i].ipAddress.seg[2] = 168;
		dynamicIPPool[i].ipAddress.seg[1] = 1;   dynamicIPPool[i].ipAddress.seg[0] = 3+i;
		dynamicIPPool[i].isFree = true;
	}
	//静态IP池初始化
	for (int i = 0; i < sizeof(staticIPPool) / sizeof(StaticIPManege); i++)
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

void DataManege::importData(DynamicIPManage *IPData)
{
	IPPool = IPData;
	flag = true;
}
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
				Ip->address = staticIPPool->IPData.ipAddress.address;
				return 0;
			}
		
		}
		return -1;//没有匹配返回-1；
}

StaticIPManege* DataManege::getIPdata()
{
	return staticIPPool;
}
