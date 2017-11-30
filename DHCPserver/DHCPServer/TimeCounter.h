#pragma once
#include<ctime>  
#include<iostream>  
#include <process.h>  
#include <windows.h>  
//#include "DHCPPackageServer.h"
#include "DataManage.h"
using std::cout;
using std::cin;
using std::endl;
using std::flush;

class Clock {
	int h;
	int m;
	int s;
	HANDLE m_handle[2];
	int handleCnt;
	int flag;
	bool endFlag;
	DataManege *clockData;
	char mac[18];
public:
	 Clock(DataManege *ClockData);
	void begin(); //��ʼ����������ʼ�趨��Լʱ��Ϊ0:1:0��һ����
	void setMac(char *Mac);//�趨Ҫά���Ŀͻ��˱�ʶ
	void set(int hour, int min, int sec);//set(int ,int ,int )  
	void tick();
	void show();
	friend DWORD WINAPI runFuction(LPVOID lpParameter);
	void run();
	bool getEndFlag();

};

