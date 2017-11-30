#pragma once
#include"DHCPPackageBasic.h"
#include "DataManage.h"


class DHCPPackageServer :public DHCPPackageBasic
{
public:
	DHCPPackageServer(DHCPMessageStuct *Meassage);
	void begin();
	void setTime(uint8_t *Time);   //设定租约时间
//	void begin(DynamicIPManage *DynamicIPPool, StaticIPManege *StaticIPPool);
//	int package(DHCPMessageStuct *Meassage, int MeassageType);//考虑服务器也许不需要单独产生报文
	int analysis(DHCPMessageStuct *Meassage);
	int addOption1(DHCPMessageStuct *Meassage); //掩码
	int addOption3(DHCPMessageStuct *Meassage); //网关
	int addOption51(DHCPMessageStuct *Meassage, uint8_t *Time);//租借时间
	int addOption53(DHCPMessageStuct *Meassage);//报文类型
	int package(DHCPMessageStuct *Message);//打包报文
	bool getState();//获取运行状态，判断是否完成
	DHCPMessageStuct getRecvMessage();
	int setData(DataManege *ServerData);  //传入数据管理类
	void reflash();//刷新IP状态


private:
	DHCPMessageStuct recvMessage;
	bool DHCPFinish;                 //判断是否完成配置。
	DataManege *serverData;
	Address IPBuf;           //IP地址缓存，解决访问报文类型不确定时，回复报文的IP地址选择问题。
	int IPDistribution(DHCPMessageStuct *Meassage);
	uint8_t time[3];
};
