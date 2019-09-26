// main.cpp : 定义控制台应用程序的入口点。
//

#include "ThreadPool.h"
#include "TaskTest.h"
#include <windows.h>
#include <memory>


int main()
{
	std::shared_ptr<ThreadPool> pool(new ThreadPool());

	for (int i = 0; i < 5; i++) {
		pool->addTask(std::shared_ptr<TaskBase>(new TaskTest(20)));
	}
	pool->run(5);

	/*while (1) {
		Sleep(1000);
	}*/
	Sleep(10000);
	pool->stop();
	return 0;
}

