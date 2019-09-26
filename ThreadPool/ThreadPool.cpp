// ThreadPool.cpp : 定义控制台应用程序的入口点。
//
#include "ThreadPool.h"




ThreadPool::ThreadPool()
{
	/*DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];
	for (int i = 0; i < MAX_THREADS; ++i) {
		hThread[i] = CreateThread(0, 64, ThreadProc, this, STACK_SIZE_PARAM_IS_A_RESERVATION, &dwThreadId[i]);
		if (0 == hThread[i]) {
			DWORD e = GetLastError();
			printf("%d\r\n", e);
			break;
		}
	}*/
}


ThreadPool::~ThreadPool()
{
}

void ThreadPool::run(int num)
{
	for (int i = 0; i < num; ++i) {
		ThreadData data;
		data.hThread = CreateThread(0, 256, ThreadProc, this, STACK_SIZE_PARAM_IS_A_RESERVATION, &data.dwThreadId);
		if (0 == data.hThread) {
			DWORD e = GetLastError();
			printf("%d\r\n", e);
			break;
		}
		vecThreadData.push_back(data);
	}
}

void ThreadPool::addTask(TaskBase *pTask)
{
	queTask.push(pTask);
}

DWORD WINAPI ThreadPool::ThreadProc(LPVOID lpParam) {
	while (1) {
		//Sleep(10000);
		//printf("%d\r\n", GetCurrentThreadId());
		ThreadPool * pPool = static_cast<ThreadPool *>(lpParam);
		if (pPool->queTask.size() > 0) {
			TaskBase* pTask = pPool->queTask.front();
			pPool->queTask.pop();
			if (pTask) {
				pTask->run();
			}
		}
	}
	return 0;
}
