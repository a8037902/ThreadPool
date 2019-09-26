#pragma once
class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase();

	virtual void run()=0;
};

