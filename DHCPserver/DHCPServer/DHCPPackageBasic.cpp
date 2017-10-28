#include "DHCPPackageBasic.h"

DHCPPackageBasic::DHCPPackageBasic()
{

}


int DHCPPackageBasic::MACAGet(char *Mac)
{
	NCB ncb;                                  //定义一个NCB(网络控制块)类型的结构体变量ncb  
	typedef struct _ASTAT_
	{
		ADAPTER_STATUS   adapt;
		NAME_BUFFER   NameBuff[30];
	}ASTAT, *PASTAT;
	ASTAT Adapter;

	typedef struct _LANA_ENUM
	{
		UCHAR length;
		UCHAR lana[MAX_LANA];
	}LANA_ENUM;
	LANA_ENUM lana_enum;

	//取得网卡信息列表       
	UCHAR uRetCode;
	memset(&ncb, 0, sizeof(ncb));                         //将已开辟内存空间ncb 的值均设为值 0  
	memset(&lana_enum, 0, sizeof(lana_enum));                     //清空一个结构类型的变量lana_enum，赋值为0  

																  //对结构体变量ncb赋值  
	ncb.ncb_command = NCBENUM;                        //统计系统中网卡的数量  
	ncb.ncb_buffer = (unsigned char *)&lana_enum;                     //ncb_buffer成员指向由LANA_ENUM结构填充的缓冲区  
	ncb.ncb_length = sizeof(LANA_ENUM);

	//向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡，每个网卡的编号（Mac地址）   
	uRetCode = Netbios(&ncb);                         //调用netbois(ncb)获取网卡序列号      
	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	//对每一个网卡，以其网卡编号为输入编号，获取其Mac地址     
	for (int lana = 0; lana < lana_enum.length; lana++)
	{
		ncb.ncb_command = NCBRESET;                   //对网卡发送NCBRESET命令，进行初始化  
		ncb.ncb_lana_num = lana_enum.lana[lana];
		uRetCode = Netbios(&ncb);
		if (uRetCode == NRC_GOODRET)
			break;
	}
	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	// 准备取得接口卡的状态块取得Mac地址  
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBASTAT;                  //对网卡发送NCBSTAT命令，获取网卡信息  
	ncb.ncb_lana_num = lana_enum.lana[0];                    //指定网卡号   
	strcpy((char*)ncb.ncb_callname, "*");                //远程系统名赋值为*  
	ncb.ncb_buffer = (unsigned char *)&Adapter;              //指定返回的信息存放的变量  
	ncb.ncb_length = sizeof(Adapter);

	//接着发送NCBASTAT命令以获取网卡的信息  
	uRetCode = Netbios(&ncb);

	// 取得网卡的信息，并且如果网卡正常工作的话，返回标准的冒号分隔格式。     
	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	sprintf(Mac, "%02X-%02X-%02X-%02X-%02X-%02X",
		Adapter.adapt.adapter_address[0],
		Adapter.adapt.adapter_address[1],
		Adapter.adapt.adapter_address[2],
		Adapter.adapt.adapter_address[3],
		Adapter.adapt.adapter_address[4],
		Adapter.adapt.adapter_address[5]
		);
	return 0;
}