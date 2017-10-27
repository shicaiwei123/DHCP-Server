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
	socketBasic();//构造函数
	int begin();  	//初始化WSA
	int socketCreate(int protocol);//创建基础socket套接字
	SOCKET socketGet();


};
