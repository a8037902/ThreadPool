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
	};
public:
	ThreadPool();
	virtual ~ThreadPool();

	void run(int);
	void addTask(TaskBase*);

private:
	static DWORD WINAPI ThreadProc(LPVOID lpParam);

	std::vector<ThreadData> vecThreadData;
	std::queue<TaskBase*> queTask;
};

