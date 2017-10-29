#include "DataManege.h"

DataManege::DataManege()
{
	memset(&clientData, 0, sizeof(clientData));
}

int DataManege::dataFresh(DHCPMessageStuct *recvMessage)
{
	clientData.addressLeaseTime = recvMessage->option.addressLeaseTime;
	clientData.ipAdderss = recvMessage->hdr.yiaddr;
	clientData.routerAddress = recvMessage->option.routerAddress;
	clientData.subnetMask = recvMessage->option.subnetMask;
	return 0;
}

ClientData DataManege::getClientData()
{
	return clientData;
}