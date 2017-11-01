#pragma once
#include "DHCPPackageBasic.h"
/*客户端报文处理类*/
//结合客户端需求，基于报文处理基类增加了一些方法和数据
//封装了选项中的报文类型
//报文封装和选项提供了两种接口，兼容需要生成指定报文类型的需求
class DHCPPackageClient :public DHCPPackageBasic
{
public:
	DHCPPackageClient(DHCPMessageStuct *Meassage);
	int package(DHCPMessageStuct *Meassage, int MeassageType);
	int addOption53(DHCPMessageStuct *Meassage, int MeassageType);
	int analysis(DHCPMessageStuct *Meassage);
	bool getState();
	//重载函数，封装
	void package();
	void addOption53();
	

private:
	DHCPMessageStuct recvMessage;
	bool DHCPFinish;                 //判断是否完成配置。
};


