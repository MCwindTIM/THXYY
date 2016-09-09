#ifndef THSCHEDULER_H
#define THSCHEDULER_H

#include "THObject.h"
#include "THList.h"
#include "THFrameTimer.h"

namespace THEngine
{
	class Scheduler : public Object
	{
	private:
		LinkedList<FrameTimer*> frameTimerList;

	public:
		Scheduler();
		virtual ~Scheduler();

		void Update();

		inline void AddTimer(FrameTimer* timer) { frameTimerList.Add(timer); }
	};
}

#endif