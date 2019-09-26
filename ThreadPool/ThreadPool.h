#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <queue>
#include <mutex>
#include "TaskBase.h"

class ThreadPool
{
	struct ThreadData
	{
		DWORD dwThreadId;
		HANDLE hThread;
		HANDLE hExitEvent;
	};

	struct ThreadParam
	{
		HANDLE hExitEvent;
		ThreadPool *pPool;
	};
public:
	ThreadPool();
	virtual ~ThreadPool();

	void run(int);
	void stop();
	void addTask(std::shared_ptr<TaskBase>);
	std::shared_ptr<TaskBase> popTask();

private:
	static DWORD WINAPI ThreadProc(LPVOID lpParam);

	std::vector<ThreadData> vecThreadData;
	std::queue<std::shared_ptr<TaskBase>> queTask;

	std::mutex mutex;
	bool isExit;
};

