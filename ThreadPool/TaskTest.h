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
	TaskTest(unsigned int times=0);
	virtual ~TaskTest();

	virtual bool run();

	unsigned int id;
	unsigned int times;
};


