#include "TaskTest.h"


TaskTest::TaskTest(unsigned int times):TaskBase()
{
	id = cnt;
	this->times = times;
}


TaskTest::~TaskTest()
{
}

bool TaskTest::run()
{
	printf("id=%d,cnt=%d,%d\r\n", id,cnt,GetCurrentThreadId());
	Sleep(1000);
	if (this->times) {
		if (--this->times)return true;
		else return false;
	}
	return true;
}
