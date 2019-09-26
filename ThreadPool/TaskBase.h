#pragma once
class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase();

	virtual bool run()=0;

	static unsigned int cnt;
};



