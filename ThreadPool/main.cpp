// main.cpp
//

#include "ThreadPool.h"
#include "TaskTest.h"
#include <windows.h>
#include <memory>


int main()
{
	srand(0);
	std::shared_ptr<ThreadPool> pool(new ThreadPool());

	for (int i = 0; i < 5; i++) {
		pool->addTask(std::shared_ptr<TaskBase>(new TaskTest(20)));
	}
	for (int i = 0; i < 5; i++) {
		pool->addTask(std::shared_ptr<TaskBase>(new TaskTest(5)));
	}
	pool->run(5);

	/*while (1) {
		Sleep(1000);
	}*/
	Sleep(100000);
	pool->stop();
	return 0;
}

