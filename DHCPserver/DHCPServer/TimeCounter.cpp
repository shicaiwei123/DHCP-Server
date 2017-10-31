#include "TimeCounter.h"
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