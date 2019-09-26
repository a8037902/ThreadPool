#pragma once
#include "TaskBase.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
class TaskTest :
	public TaskBase
{
public:
	TaskTest();
	virtual ~TaskTest();

	virtual void run();
};

