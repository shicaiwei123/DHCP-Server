#pragma once
/*报文处理的基类*/
//定义了一个报文处理的抽象类，统一报文处理的必备接口
#include "DHCPDataStruct.h"
#include "SocketBasic.h"
#include <windef.h>                     //该头文件定义了Windows的所有数据基本型态  
#include <Nb30.h>                   //该头文件声明了netbios的所有的函数   
#pragma comment(lib,"netapi32.lib")               //连接Netapi32.lib库，MAC获取中用到了NetApi32.DLL的功能  

class DHCPPackageBasic
{
public:
	DHCPPackageBasic(DHCPMessageStuct *Message);
	int MACAGet(char *Mac);//获取本机MAC地址
	virtual int package(DHCPMessageStuct *Meassage, int MeassageType)=0;//报文封装
	virtual int analysis(DHCPMessageStuct *Meassage)=0;
protected:
	DHCPMessageStuct *meassage;
	int meassageType;
};




