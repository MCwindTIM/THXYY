#include "THScheduler.h"

namespace THEngine
{
	Scheduler::Scheduler()
	{

	}

	Scheduler::~Scheduler()
	{

	}

	void Scheduler::Update()
	{
		auto iter = frameTimerList.GetIterator();
		while (iter->HasNext())
		{
			auto timer = iter->Next();

			if (timer->IsPaused() == false)
			{
				timer->frameLeft--;
				if (timer->frameLeft == 0)
				{
					timer->run();
					iter->Remove();
				}
			}
		}
	}
}