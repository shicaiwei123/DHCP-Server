//#include <winsock2.h>                   //��ͷ�ļ�������Socket��̵Ĺ���  
//#include <stdio.h>                          //��ͷ�ļ��������������������  
//#pragma comment(lib,"ws2_32.lib")   //����ws2_32.lib��.ֻҪ�������õ�Winsock API ��������Ҫ�õ� Ws2_32.lib  
//#include <windef.h>                     //��ͷ�ļ�������Windows���������ݻ�����̬  
//#include <Nb30.h>                   //��ͷ�ļ�������netbios�����еĺ���   
//#pragma comment(lib,"netapi32.lib")               //����Netapi32.lib�⣬MAC��ȡ���õ���NetApi32.DLL�Ĺ���  
//#include <string>
//using std::string;
//
//////#include <stdlib.h>                     //��ͷ�ļ�������һЩͨ�ú���  
//////#include <httpext.h>                    //��ͷ�ļ�֧��HTTP����  
////// //using namespace System;
//////
//////int getMAC(char * mac)                                    //��NetAPI����ȡ����MAC��ַ  
//////{
//////	NCB ncb;                                  //����һ��NCB(������ƿ�)���͵Ľṹ�����ncb  
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
//////	//ȡ��������Ϣ�б�       
//////	UCHAR uRetCode;
//////	memset(&ncb, 0, sizeof(ncb));                         //���ѿ����ڴ�ռ�ncb ��ֵ����Ϊֵ 0  
//////	memset(&lana_enum, 0, sizeof(lana_enum));                     //���һ���ṹ���͵ı���lana_enum����ֵΪ0  
//////
//////																  //�Խṹ�����ncb��ֵ  
//////	ncb.ncb_command = NCBENUM;                        //ͳ��ϵͳ������������  
//////	ncb.ncb_buffer = (unsigned char *)&lana_enum;                     //ncb_buffer��Աָ����LANA_ENUM�ṹ���Ļ�����  
//////	ncb.ncb_length = sizeof(LANA_ENUM);
//////
//////	//����������NCBENUM����Ի�ȡ��ǰ������������Ϣ�����ж��ٸ�������ÿ�������ı�ţ�MAC��ַ��   
//////	uRetCode = Netbios(&ncb);                         //����netbois(ncb)��ȡ�������к�      
//////	if (uRetCode != NRC_GOODRET)
//////		return uRetCode;
//////
//////	//��ÿһ�������������������Ϊ�����ţ���ȡ��MAC��ַ     
//////	for (int lana = 0; lana < lana_enum.length; lana++)
//////	{
//////		ncb.ncb_command = NCBRESET;                   //����������NCBRESET������г�ʼ��  
//////		ncb.ncb_lana_num = lana_enum.lana[lana];
//////		uRetCode = Netbios(&ncb);
//////		if (uRetCode == NRC_GOODRET)
//////			break;
//////	}
//////	if (uRetCode != NRC_GOODRET)
//////		return uRetCode;
//////
//////	// ׼��ȡ�ýӿڿ���״̬��ȡ��MAC��ַ  
//////	memset(&ncb, 0, sizeof(ncb));
//////	ncb.ncb_command = NCBASTAT;                  //����������NCBSTAT�����ȡ������Ϣ  
//////	ncb.ncb_lana_num = lana_enum.lana[0];                    //ָ��������   
//////	strcpy((char*)ncb.ncb_callname, "*");                //Զ��ϵͳ����ֵΪ*  
//////	ncb.ncb_buffer = (unsigned char *)&Adapter;              //ָ�����ص���Ϣ��ŵı���  
//////	ncb.ncb_length = sizeof(Adapter);
//////
//////	//���ŷ���NCBASTAT�����Ի�ȡ��������Ϣ  
//////	uRetCode = Netbios(&ncb);
//////
//////	// ȡ����������Ϣ����������������������Ļ������ر�׼��ð�ŷָ���ʽ��     
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
//////	printf(" mac��ַ : %s \n", mac);
//////
//////	return 0;
//////}
////
////
//////IP�洢
////#include <iostream>
////using namespace std;
////class IP
////{
////private:
////	union
////	{
////		unsigned char seg[4]; //IP��ַ��4�ֽڣ����߿����޷����ַ�������ָ4����
////		unsigned int address; //���߿���һ������
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
////	//���渳ֵ��˳���漰�������ݴ洢�ṹ���ο�[�������������ڴ�����δ洢����](http://blog.csdn.net/sxhelijian/article/details/51015706)
////	seg[0] = s3;
////	seg[1] = s2;
////	seg[2] = s1;
////	seg[3] = s0;
////}
////
////void IP::showIP()
////{
////	//��ʾ������Ǹ��˿��ģ���4�κ���
////	cout << int(seg[3]) << "." << int(seg[2]) << "." << int(seg[1]) << "." << int(seg[0]) << endl;
////	return;
////}
////
////bool IP::sameSubnet(const IP &ip, const IP &mark)
////{
////	//���������밴λ�룬�Ǽ�����ڲ��Ĳ�����ֱ����һ���������������
////	unsigned int i1, i2;
////	i1 = address&mark.address; //�������������߼�������
////	i2 = ip.address&mark.address; //�������������߼�������
////	return (i1 == i2); //������������߼�����������ͬ��������ͬһ����
////}
////
////char IP::whatKind()
////{
////	//IP��ַ�����ͣ��뵽�ٶȰٿ���������IP��ַ��
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
////		cout << "����IP��ͬһ����" << endl;
////	else
////		cout << "����IP����ͬһ����" << endl;
////	cout << "ip1����" << ip1.whatKind() << "������" << endl;
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
//	NCB ncb;                                  //����һ��NCB(������ƿ�)���͵Ľṹ�����ncb  
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
//	//ȡ��������Ϣ�б�       
//	UCHAR uRetCode;
//	memset(&ncb, 0, sizeof(ncb));                         //���ѿ����ڴ�ռ�ncb ��ֵ����Ϊֵ 0  
//	memset(&lana_enum, 0, sizeof(lana_enum));                     //���һ���ṹ���͵ı���lana_enum����ֵΪ0  
//
//																  //�Խṹ�����ncb��ֵ  
//	ncb.ncb_command = NCBENUM;                        //ͳ��ϵͳ������������  
//	ncb.ncb_buffer = (unsigned char *)&lana_enum;                     //ncb_buffer��Աָ����LANA_ENUM�ṹ���Ļ�����  
//	ncb.ncb_length = sizeof(LANA_ENUM);
//
//	//����������NCBENUM����Ի�ȡ��ǰ������������Ϣ�����ж��ٸ�������ÿ�������ı�ţ�Mac��ַ��   
//	uRetCode = Netbios(&ncb);                         //����netbois(ncb)��ȡ�������к�      
//	if (uRetCode != NRC_GOODRET)
//		return uRetCode;
//
//	//��ÿһ�������������������Ϊ�����ţ���ȡ��Mac��ַ     
//	for (int lana = 0; lana < lana_enum.length; lana++)
//	{
//		ncb.ncb_command = NCBRESET;                   //����������NCBRESET������г�ʼ��  
//		ncb.ncb_lana_num = lana_enum.lana[lana];
//		uRetCode = Netbios(&ncb);
//		if (uRetCode == NRC_GOODRET)
//			break;
//	}
//	if (uRetCode != NRC_GOODRET)
//		return uRetCode;
//
//	// ׼��ȡ�ýӿڿ���״̬��ȡ��Mac��ַ  
//	memset(&ncb, 0, sizeof(ncb));
//	ncb.ncb_command = NCBASTAT;                  //����������NCBSTAT�����ȡ������Ϣ  
//	ncb.ncb_lana_num = lana_enum.lana[0];                    //ָ��������   
//	strcpy((char*)ncb.ncb_callname, "*");                //Զ��ϵͳ����ֵΪ*  
//	ncb.ncb_buffer = (unsigned char *)&Adapter;              //ָ�����ص���Ϣ��ŵı���  
//	ncb.ncb_length = sizeof(Adapter);
//
//	//���ŷ���NCBASTAT�����Ի�ȡ��������Ϣ  
//	uRetCode = Netbios(&ncb);
//
//	// ȡ����������Ϣ����������������������Ļ������ر�׼��ð�ŷָ���ʽ��     
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
//	//// linux c/c++ IP�ַ���ת���ɿɱȽϴ�С������
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
	time_t t = time(NULL);//ȡ�õ�ǰʱ��  
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
	cout << "�����뵹��ʱ��ʱ�䣺";
	int h1, m1, s1;
	cin >> h1 >> m1 >> s1;
	c.set(h1, m1, s1);
	c.run();
}
