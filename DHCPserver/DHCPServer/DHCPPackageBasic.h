#pragma once
#include "DHCPDataStruct.h"
#include "SocketBasic.h"
#include <windef.h>                     //该头文件定义了Windows的所有数据基本型态  
#include <Nb30.h>                   //该头文件声明了netbios的所有的函数   
#pragma comment(lib,"ws2_32.lib")                 //连接ws2_32.lib库.只要程序中用到Winsock API 函数，都要用到 Ws2_32.lib  
#pragma comment(lib,"netapi32.lib")               //连接Netapi32.lib库，MAC获取中用到了NetApi32.DLL的功能  

class DHCPPackageBasic
{
public:
	DHCPPackageBasic(DHCPMessageStuct *Message);
	int MACAGet(char *Mac);//获取本机MAC地址
	virtual int package(DHCPMessageStuct *Meassage, int MeassageType)=0;//报文封装

protected:
	DHCPMessageStuct *meassage;
	int meassageType;
};




