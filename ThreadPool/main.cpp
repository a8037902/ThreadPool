// main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "ThreadPool.h"
#include "TaskTest.h"
#include <windows.h>
#include <memory>


int main()
{
	
	std::shared_ptr<ThreadPool> pool(new ThreadPool());
	pool->addTask(new TaskTest());
	pool->addTask(new TaskTest());
	pool->addTask(new TaskTest());
	pool->addTask(new TaskTest());
	pool->addTask(new TaskTest());
	pool->run(1);

	while (1) {
		Sleep(1000);
	}

	return 0;
}

