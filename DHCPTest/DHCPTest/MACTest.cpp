//#include <winsock2.h>                   //该头文件定义了Socket编程的功能  
//#include <stdio.h>                          //该头文件声明了输入输出流函数  
//#pragma comment(lib,"ws2_32.lib")   //连接ws2_32.lib库.只要程序中用到Winsock API 函数，都要用到 Ws2_32.lib  
//#include <windef.h>                     //该头文件定义了Windows的所有数据基本型态  
//#include <Nb30.h>                   //该头文件声明了netbios的所有的函数   
//#pragma comment(lib,"netapi32.lib")               //连接Netapi32.lib库，MAC获取中用到了NetApi32.DLL的功能  
//#include <string>
//using std::string;
//
//////#include <stdlib.h>                     //该头文件定义了一些通用函数  
//////#include <httpext.h>                    //该头文件支持HTTP请求  
////// //using namespace System;
//////
//////int getMAC(char * mac)                                    //用NetAPI来获取网卡MAC地址  
//////{
//////	NCB ncb;                                  //定义一个NCB(网络控制块)类型的结构体变量ncb  
//////	typedef struct _ASTAT_
//////	{
//////		ADAPTER_STATUS   adapt;
//////		NAME_BUFFER   NameBuff[30];
//////	}ASTAT, *PASTAT;
//////	ASTAT Adapter;
//////
//////	typedef struct _LANA_ENUM
//////	{
//////		UCHAR length;
//////		UCHAR lana[MAX_LANA];
//////	}LANA_ENUM;
//////	LANA_ENUM lana_enum;
//////
//////	//取得网卡信息列表       
//////	UCHAR uRetCode;
//////	memset(&ncb, 0, sizeof(ncb));                         //将已开辟内存空间ncb 的值均设为值 0  
//////	memset(&lana_enum, 0, sizeof(lana_enum));                     //清空一个结构类型的变量lana_enum，赋值为0  
//////
//////																  //对结构体变量ncb赋值  
//////	ncb.ncb_command = NCBENUM;                        //统计系统中网卡的数量  
//////	ncb.ncb_buffer = (unsigned char *)&lana_enum;                     //ncb_buffer成员指向由LANA_ENUM结构填充的缓冲区  
//////	ncb.ncb_length = sizeof(LANA_ENUM);
//////
//////	//向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡，每个网卡的编号（MAC地址）   
//////	uRetCode = Netbios(&ncb);                         //调用netbois(ncb)获取网卡序列号      
//////	if (uRetCode != NRC_GOODRET)
//////		return uRetCode;
//////
//////	//对每一个网卡，以其网卡编号为输入编号，获取其MAC地址     
//////	for (int lana = 0; lana < lana_enum.length; lana++)
//////	{
//////		ncb.ncb_command = NCBRESET;                   //对网卡发送NCBRESET命令，进行初始化  
//////		ncb.ncb_lana_num = lana_enum.lana[lana];
//////		uRetCode = Netbios(&ncb);
//////		if (uRetCode == NRC_GOODRET)
//////			break;
//////	}
//////	if (uRetCode != NRC_GOODRET)
//////		return uRetCode;
//////
//////	// 准备取得接口卡的状态块取得MAC地址  
//////	memset(&ncb, 0, sizeof(ncb));
//////	ncb.ncb_command = NCBASTAT;                  //对网卡发送NCBSTAT命令，获取网卡信息  
//////	ncb.ncb_lana_num = lana_enum.lana[0];                    //指定网卡号   
//////	strcpy((char*)ncb.ncb_callname, "*");                //远程系统名赋值为*  
//////	ncb.ncb_buffer = (unsigned char *)&Adapter;              //指定返回的信息存放的变量  
//////	ncb.ncb_length = sizeof(Adapter);
//////
//////	//接着发送NCBASTAT命令以获取网卡的信息  
//////	uRetCode = Netbios(&ncb);
//////
//////	// 取得网卡的信息，并且如果网卡正常工作的话，返回标准的冒号分隔格式。     
//////	if (uRetCode != NRC_GOODRET)
//////		return uRetCode;
//////
//////	sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X",
//////		Adapter.adapt.adapter_address[0],
//////		Adapter.adapt.adapter_address[1],
//////		Adapter.adapt.adapter_address[2],
//////		Adapter.adapt.adapter_address[3],
//////		Adapter.adapt.adapter_address[4],
//////		Adapter.adapt.adapter_address[5]
//////		);
//////	return 0;
//////}
//////
//////int main()
//////{
//////
//////	//CheckIP();
//////	char   mac[16];
//////	getMAC(mac);
//////	printf(" mac地址 : %s \n", mac);
//////
//////	return 0;
//////}
////
////
//////IP存储
////#include <iostream>
////using namespace std;
////class IP
////{
////private:
////	union
////	{
////		unsigned char seg[4]; //IP地址共4字节，或者看成无符号字符数组所指4部分
////		unsigned int address; //或者看成一个整体
////
////	};
////public:
////	IP(int = 0, int = 0, int = 0, int = 0);
////	void showIP();
////	bool sameSubnet(const IP &ip, const IP &mark);
////	char whatKind();
////};
////
////IP::IP(int s0, int s1, int s2, int s3)
////{
////	//下面赋值的顺序，涉及整型数据存储结构，参考[《整型数据在内存中如何存储？》](http://blog.csdn.net/sxhelijian/article/details/51015706)
////	seg[0] = s3;
////	seg[1] = s2;
////	seg[2] = s1;
////	seg[3] = s0;
////}
////
////void IP::showIP()
////{
////	//显示结果，是给人看的，分4段合适
////	cout << int(seg[3]) << "." << int(seg[2]) << "." << int(seg[1]) << "." << int(seg[0]) << endl;
////	return;
////}
////
////bool IP::sameSubnet(const IP &ip, const IP &mark)
////{
////	//与子网掩码按位与，是计算机内部的操作，直接以一个整体操作更方便
////	unsigned int i1, i2;
////	i1 = address&mark.address; //和子网掩码作逻辑与运算
////	i2 = ip.address&mark.address; //和子网掩码作逻辑与运算
////	return (i1 == i2); //与子网掩码的逻辑与运算结果相同，则属于同一子网
////}
////
////char IP::whatKind()
////{
////	//IP地址的类型，请到百度百科中搜索《IP地址》
////	if (seg[3] < 128)
////		return 'A';
////	else if (seg[3] < 192)
////		return 'B';
////	else if (seg[3] < 224)
////		return 'C';
////	else if (seg[3] < 240)
////		return 'D';
////	else
////		return 'E';
////}
////
////int main()
////{
////	IP ip1(202, 194, 116, 97), ip2(202, 194, 119, 102), mark(255, 255, 248, 0);
////	cout << "ip1: ";
////	ip1.showIP();
////	cout << "ip2: ";
////	ip2.showIP();
////	if (ip1.sameSubnet(ip2, mark))
////		cout << "两个IP在同一子网" << endl;
////	else
////		cout << "两个IP不在同一子网" << endl;
////	cout << "ip1属于" << ip1.whatKind() << "类网络" << endl;
////	return 0;
////}
//
//#include <iomanip>
//#include <iostream>
//using namespace std;
//#include "stdio.h"
//#include <string>
//int MACAGet(char *Mac)
//{
//	NCB ncb;                                  //定义一个NCB(网络控制块)类型的结构体变量ncb  
//	typedef struct _ASTAT_
//	{
//		ADAPTER_STATUS   adapt;
//		NAME_BUFFER   NameBuff[30];
//	}ASTAT, *PASTAT;
//	ASTAT Adapter;
//
//	typedef struct _LANA_ENUM
//	{
//		UCHAR length;
//		UCHAR lana[MAX_LANA];
//	}LANA_ENUM;
//	LANA_ENUM lana_enum;
//
//	//取得网卡信息列表       
//	UCHAR uRetCode;
//	memset(&ncb, 0, sizeof(ncb));                         //将已开辟内存空间ncb 的值均设为值 0  
//	memset(&lana_enum, 0, sizeof(lana_enum));                     //清空一个结构类型的变量lana_enum，赋值为0  
//
//																  //对结构体变量ncb赋值  
//	ncb.ncb_command = NCBENUM;                        //统计系统中网卡的数量  
//	ncb.ncb_buffer = (unsigned char *)&lana_enum;                     //ncb_buffer成员指向由LANA_ENUM结构填充的缓冲区  
//	ncb.ncb_length = sizeof(LANA_ENUM);
//
//	//向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡，每个网卡的编号（Mac地址）   
//	uRetCode = Netbios(&ncb);                         //调用netbois(ncb)获取网卡序列号      
//	if (uRetCode != NRC_GOODRET)
//		return uRetCode;
//
//	//对每一个网卡，以其网卡编号为输入编号，获取其Mac地址     
//	for (int lana = 0; lana < lana_enum.length; lana++)
//	{
//		ncb.ncb_command = NCBRESET;                   //对网卡发送NCBRESET命令，进行初始化  
//		ncb.ncb_lana_num = lana_enum.lana[lana];
//		uRetCode = Netbios(&ncb);
//		if (uRetCode == NRC_GOODRET)
//			break;
//	}
//	if (uRetCode != NRC_GOODRET)
//		return uRetCode;
//
//	// 准备取得接口卡的状态块取得Mac地址  
//	memset(&ncb, 0, sizeof(ncb));
//	ncb.ncb_command = NCBASTAT;                  //对网卡发送NCBSTAT命令，获取网卡信息  
//	ncb.ncb_lana_num = lana_enum.lana[0];                    //指定网卡号   
//	strcpy((char*)ncb.ncb_callname, "*");                //远程系统名赋值为*  
//	ncb.ncb_buffer = (unsigned char *)&Adapter;              //指定返回的信息存放的变量  
//	ncb.ncb_length = sizeof(Adapter);
//
//	//接着发送NCBASTAT命令以获取网卡的信息  
//	uRetCode = Netbios(&ncb);
//
//	// 取得网卡的信息，并且如果网卡正常工作的话，返回标准的冒号分隔格式。     
//	if (uRetCode != NRC_GOODRET)
//		return uRetCode;
//
//	sprintf(Mac, "%02X-%02X-%02X-%02X-%02X-%02X",
//		Adapter.adapt.adapter_address[0],
//		Adapter.adapt.adapter_address[1],
//		Adapter.adapt.adapter_address[2],
//		Adapter.adapt.adapter_address[3],
//		Adapter.adapt.adapter_address[4],
//		Adapter.adapt.adapter_address[5]
//		);
//	return 0;
//}
//
//int main(void) 
//{
//	//cout.setf(ios::showpos | ios::uppercase);
//	//cout << hex << setw(4) << 12 << setw(12) << -12 << endl;
//	//cout << dec << setw(4) << 12 << setw(12) << -12 << endl;
//	//cout << oct << setw(4) << 12 << setw(12) << -12 << endl;
//	//cout.unsetf(ios::showpos | ios::uppercase);
//	//cout << hex << setw(4) << 12 << setw(12) << -12 << endl;
//	//cout << dec << setw(4) << 12 << setw(12) << -12 << endl;
//	//cout << oct << setw(4) << 12 << setw(12) << -12 << endl;
//	//return 0;
//	//uint8_t a = 1;
//	//printf("%d\n", a);
//	//cout << dec<<char(a) << endl;
//	//return 0; 
//	//LONGLONG b = inet_addr("255.255.255.255");
//	//union IP
//	//{
//	//	LONGLONG a;
//	//	string IPAddress;
//	//};
//	//IP.a = b;
//	////string s = mysql>select inet_ntoa(a);
//	//return 0;
//
//	//using namespace std;
//	//// linux c/c++ IP字符串转换成可比较大小的数字
//	//// g++ -o test_ip_unsigned test_ip_unsigned.cpp
//	//	string ip = "192.168.1.123";
//	//	unsigned int x = ntohl(inet_addr(ip.c_str()));
//	//	unsigned int y = (unsigned int)192 * 256 * 256 * 256 + 168 * 256 * 256 + 256 + 123;
//	//	printf("x=[%u] ip un[%u]rn", x, y);
//	//	return 1;
//
//	//char a[18] = "00-50-56-C0-00-08";
//	//char b[18] = "30-52-CB-61-90-2F";
//	//uint8_t mac[1][18];
//	//memcpy(mac[0], "30-52-CB-61-90-6F", 18);
//	//int c =strcmp((char*)mac[0],b);
//	//return 0;
//
//}
//

#include<iostream>  
using namespace std;
#include<ctime>  
class Clock {
	int h;
	int m;
	int s;
public:
	void set(int hour, int min, int sec);//set(int ,int ,int )  
	void tick();
	void show();
	void run();
};

void Clock::set(int hour, int min, int sec)
{
	h = hour;
	m = min;
	s = sec;
}
void Clock::tick()
{
	time_t t = time(NULL);//取得当前时间  
	while (time(NULL) == t);
	if (--s < 0) {
		s = 59;
		if (--m < 0) {
			m = 59;
			--h < 0;
		}
	}
}
void Clock::show()
{
	cout << '\r';
	if (h < 10)cout << 0;
	cout << h << ':';
	if (m < 10)cout << 0;
	cout << m << ':';
	if (s < 10)cout << 0;
	cout << s << flush;
}
void Clock::run()
{
	while (h != 0 || m != 0 || s != 0) {
		tick();
		show();
	}
	cout << endl << "Time out!" << endl;
	cout << '\a';
}
int main()
{
	Clock c;
	cout << "请输入倒计时的时间：";
	int h1, m1, s1;
	cin >> h1 >> m1 >> s1;
	c.set(h1, m1, s1);
	c.run();
}
