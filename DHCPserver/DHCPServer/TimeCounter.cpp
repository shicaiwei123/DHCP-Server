#include "TimeCounter.h"
void Clock::set(int hour, int min, int sec)
{
	h = hour;
	m = min;
	s = sec;
	handleCnt = 0;
	flag = 0;
}
Clock::Clock(DataManege *ClockData)
{
	clockData = ClockData;
}

 void Clock::begin()
 {
	 h = 0;
	 m = 1;
	 s = 0;
	 handleCnt = 0;
	 flag = 0;
	 endFlag = false;

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
	set(h,m,s);
	if (flag == 1)
	{
		CloseHandle(m_handle[handleCnt]);
	}
	flag = 1;
	m_handle[handleCnt] = CreateThread(NULL, 0, runFuction, this, 0, NULL);
	//handleCnt = handleCnt + 1;
	//handleCnt = handleCnt % 2;

}

DWORD WINAPI runFuction(LPVOID lpParameter)
{
	Clock *pThis = (Clock*)lpParameter;
	while (pThis->h != 0 || pThis->m != 0 || pThis->s != 0) {
		pThis->tick();
		pThis->show();
	}
	cout << endl << "Time out!" << endl;
	cout << '\a';
	pThis->endFlag = true;
	pThis->clockData->reflash(pThis->mac);
	cout << "租约超时，回收IP"<<endl;
	return 1;
}

bool Clock::getEndFlag()
{
	return endFlag;
}


void Clock::setMac(char *Mac)
{
	memcpy(mac, Mac, 18);
}