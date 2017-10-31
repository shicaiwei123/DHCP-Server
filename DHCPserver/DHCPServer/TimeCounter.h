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
public:
	void set(int hour, int min, int sec);//set(int ,int ,int )  
	void tick();
	void show();
	void run();
};
