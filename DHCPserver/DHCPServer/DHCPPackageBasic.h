#pragma once
#include "DHCPDataStruct.h"
#include "SocketBasic.h"
#include <windef.h>                     //��ͷ�ļ�������Windows���������ݻ�����̬  
#include <Nb30.h>                   //��ͷ�ļ�������netbios�����еĺ���   
#pragma comment(lib,"ws2_32.lib")                 //����ws2_32.lib��.ֻҪ�������õ�Winsock API ��������Ҫ�õ� Ws2_32.lib  
#pragma comment(lib,"netapi32.lib")               //����Netapi32.lib�⣬MAC��ȡ���õ���NetApi32.DLL�Ĺ���  

class DHCPPackageBasic
{
public:
	DHCPPackageBasic(DHCPMessageStuct *Message);
	int MACAGet(char *Mac);//��ȡ����MAC��ַ
	virtual int package(DHCPMessageStuct *Meassage, int MeassageType)=0;//���ķ�װ

protected:
	DHCPMessageStuct *meassage;
	int meassageType;
};




