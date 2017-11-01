#pragma once
/*客户端数据管理类*/
//完成客户端网络数据的刷新，数据的获取，定时器的维护
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