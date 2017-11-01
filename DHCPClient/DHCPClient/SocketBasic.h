#pragma once
//socket的基类，包含了socket的一些基本方法
//初始化，创建套接字
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")   //连接ws2_32.lib库.只要程序中用到Winsock API 函数，都要用到 Ws2_32.lib  
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
