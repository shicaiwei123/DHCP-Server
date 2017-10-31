#pragma once
#include "DHCPDataStruct.h"
#include "TimeCounter.h"
class DataManege
{
public:
	DataManege();
	int dataFresh(DHCPMessageStuct *recvMessage);
	ClientData getClientData();
	int startCounter();
private:
	ClientData clientData;
	Clock clock;

};