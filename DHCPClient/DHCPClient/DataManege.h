#pragma once
#include "DHCPDataStruct.h"
class DataManege
{
public:
	DataManege();
	int dataFresh(DHCPMessageStuct *recvMessage);
	ClientData getClientData();
private:
	ClientData clientData;

};