#pragma once
/*�ͻ������ݹ�����*/
//��ɿͻ����������ݵ�ˢ�£����ݵĻ�ȡ����ʱ����ά��
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