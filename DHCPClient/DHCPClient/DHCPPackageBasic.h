#pragma once
/*���Ĵ���Ļ���*/
//������һ�����Ĵ���ĳ����࣬ͳһ���Ĵ���ıر��ӿ�
#include "DHCPDataStruct.h"
#include "SocketBasic.h"
#include <windef.h>                     //��ͷ�ļ�������Windows���������ݻ�����̬  
#include <Nb30.h>                   //��ͷ�ļ�������netbios�����еĺ���   
#pragma comment(lib,"netapi32.lib")               //����Netapi32.lib�⣬MAC��ȡ���õ���NetApi32.DLL�Ĺ���  

class DHCPPackageBasic
{
public:
	DHCPPackageBasic(DHCPMessageStuct *Message);
	int MACAGet(char *Mac);//��ȡ����MAC��ַ
	virtual int package(DHCPMessageStuct *Meassage, int MeassageType)=0;//���ķ�װ
	virtual int analysis(DHCPMessageStuct *Meassage)=0;
protected:
	DHCPMessageStuct *meassage;
	int meassageType;
};




