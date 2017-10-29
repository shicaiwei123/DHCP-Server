#include "DataManage.h"

DataManege::DataManege()
{
	flag = false;
	IPPool = NULL;
	memset(localIPPool, 0, sizeof(localIPPool));
	
}

void DataManege::begin()
{
	//192.168.1.3--192.168.1.12
	for (int i = 0; i < sizeof(localIPPool)/sizeof(IPManage);i++)
	{
		localIPPool[i].ipAddress.seg[3] = 192;	localIPPool[i].ipAddress.seg[2] = 168;
		localIPPool[i].ipAddress.seg[1] = 1;   localIPPool[i].ipAddress.seg[0] = 3+i;
		localIPPool[i].isFree = true;
	}

}

void DataManege::importData(IPManage *IPData)
{
	IPPool = IPData;
	flag = true;
}
int DataManege::readIPPool(Address *ip)
{
	int j = 0;
	for (int i = 0; i < sizeof(localIPPool) / sizeof(IPManage);i++)
		if (localIPPool[i].isFree)
		{
			memcpy(ip, &localIPPool[i].ipAddress, sizeof(Address)); //数据赋值
			localIPPool->isFree = false;
			j++;
			break;
		}
	if (!j)  //没有空闲IP
	{
		return -1;
	}
	return 0;
}
