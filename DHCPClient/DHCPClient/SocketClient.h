#pragma once
//�̳�socket���࣬��Ͽͻ�������������һЩ����
//���ӽ���
//�����շ�
#include "SocketBasic.h"
#include "DHCPDataStruct.h"
class socketClient :public socketBasic
{
public:
	socketClient();
	int socketConnect(const char *ip, int port);//���׽���Ҫ���ʵķ���������
	DHCPMessageStuct socketRecv(char *RecvData, int Length);
	int socketSend(DHCPMessageStuct *SendMessage, int Length);
	//int socketSend(*sendData);

};
