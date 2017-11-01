#include "DataManege.h"

DataManege::DataManege()
{
	memset(&clientData, 0, sizeof(clientData));
}

int DataManege::dataFresh(DHCPMessageStuct *recvMessage)
{
	memcpy(clientData.addressLeaseTime, recvMessage->option.addressLeaseTime, sizeof(recvMessage->option.addressLeaseTime));
	clientData.ipAdderss = recvMessage->hdr.yiaddr;
	clientData.routerAddress = recvMessage->option.routerAddress;
	clientData.subnetMask = recvMessage->option.subnetMask;
	return 0;
}

ClientData DataManege::getClientData()
{
	return clientData;
}

int DataManege::startCounter()
{
	int flag;
	clock.set(clientData.addressLeaseTime[0], clientData.addressLeaseTime[1], clientData.addressLeaseTime[2]);
	flag = clock.run();
	if (flag== 1)//如果时间过半
		return 1;
}