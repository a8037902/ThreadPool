#include "TaskBase.h"

unsigned int TaskBase::cnt = 0;

TaskBase::TaskBase()
{
	cnt ++ ;
}


TaskBase::~TaskBase()
{
	cnt--;
}
