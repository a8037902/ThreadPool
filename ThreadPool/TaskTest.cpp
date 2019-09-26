#include "TaskTest.h"


TaskTest::TaskTest()
{
}


TaskTest::~TaskTest()
{
}

void TaskTest::run()
{
	printf("%d\r\n", GetCurrentThreadId());
}
