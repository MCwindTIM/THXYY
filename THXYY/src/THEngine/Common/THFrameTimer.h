#ifndef THFRAMETIMER_H
#define THFRAMETIMER_H

#include "THObject.h"

namespace THEngine
{
	class FrameTimer : public Object
	{
	private:
		int frameLeft;
		bool paused;

	public:
		FrameTimer();
		virtual ~FrameTimer();

		virtual void Exec() = 0;

		inline void Pause() { paused = true; }
		inline void Resume() { paused = false; }
		inline bool IsPaused() { return paused; }

		inline void SetFrame(int frame) { frameLeft = frame; }

		friend class Scheduler;
	};
}

#endif