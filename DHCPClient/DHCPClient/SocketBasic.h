#pragma once
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")   //����ws2_32.lib��.ֻҪ�������õ�Winsock API ��������Ҫ�õ� Ws2_32.lib  
#include<stdio.h>
class socketBasic
{
private:
	int verA;
	int verB;
protected:
	SOCKET s;
public:
	socketBasic();//���캯��
	int begin();  	//��ʼ��WSA
	int socketCreate(int protocol);//��������socket�׽���
	SOCKET socketGet();


};
