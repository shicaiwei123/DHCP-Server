#pragma once
#include <Winsock2.h>
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
