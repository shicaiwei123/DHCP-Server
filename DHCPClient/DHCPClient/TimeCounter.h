#pragma once
#include<ctime>  
#include<iostream>  
using std::cout;
using std::cin;
using std::endl;
using std::flush;
class Clock {
	int h;
	int m;
	int s;
	int timeTemp[3];
public:
	void set(int hour, int min, int sec);//set(int ,int ,int )  
	void tick();
	void show();
	int run();
};
