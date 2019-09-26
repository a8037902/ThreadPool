// ThreadPool.cpp : 定义控制台应用程序的入口点。
//
#include "ThreadPool.h"



ThreadPool::ThreadPool()
{
	isExit = false;
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
		ThreadParam *param = new ThreadParam();
		param->pPool = this;
		param->hExitEvent= CreateEvent(NULL, false, false, NULL);

		ThreadData data;
		data.hExitEvent = param->hExitEvent;
		data.hThread = CreateThread(0, 256, ThreadProc, param, STACK_SIZE_PARAM_IS_A_RESERVATION, &data.dwThreadId);
		if (0 == data.hThread) {
			DWORD e = GetLastError();
			printf("%d\r\n", e);
			delete param;
			break;
		}
		vecThreadData.push_back(data);
	}
}

void ThreadPool::stop()
{
	isExit = true;
	HANDLE *pEventHandler =new HANDLE[vecThreadData.size()];
	for (int i = 0; i < this->vecThreadData.size(); i++) {
		pEventHandler[i] = this->vecThreadData.at(i).hExitEvent;
	}
	WaitForMultipleObjects(this->vecThreadData.size(), pEventHandler, true, INFINITE);

	for (int i = 0; i < this->vecThreadData.size(); i++) {
		CloseHandle(this->vecThreadData.at(i).hThread);
		printf("close thread id=%d\r\n", this->vecThreadData.at(i).dwThreadId);
	}
	this->vecThreadData.clear();
	while (!this->queTask.empty()) this->queTask.pop();
}

void ThreadPool::addTask(std::shared_ptr<TaskBase> spTask)
{
	mutex.lock();
	this->queTask.push(spTask);
	mutex.unlock();
}

std::shared_ptr<TaskBase> ThreadPool::popTask()
{
	std::shared_ptr<TaskBase> spTask=0;
	mutex.lock();
	if (this->queTask.size() > 0) {
		spTask = this->queTask.front();
		this->queTask.pop();
	}
	mutex.unlock();
	return spTask;
}

DWORD WINAPI ThreadPool::ThreadProc(LPVOID lpParam) {
	ThreadParam * pParam = static_cast<ThreadParam *>(lpParam);
	ThreadPool* pPool = pParam->pPool;
	while (!pPool->isExit) {
		//Sleep(10000);
		//printf("%d\r\n", GetCurrentThreadId());
		
		std::shared_ptr<TaskBase> spTask = pPool->popTask();
		if (spTask) {
			if (spTask->run()) {
				pPool->addTask(spTask);
			}
		}
	}
	SetEvent(pParam->hExitEvent);
	delete pParam;
	return 0;
}
