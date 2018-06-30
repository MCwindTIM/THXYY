#ifndef THENGINEOBJECT_H
#define THENGINEOBJECT_H

#include "THObject.h"
#include "THPtr.h"

namespace THEngine
{
	class AsyncInfo;
	class Scheduler;

	class EngineObject : public Object
	{
	protected:
		Ptr<Scheduler> scheduler;
		bool paused = false;
		bool started = false;
		bool loaded = false;

	public:
		EngineObject();
		EngineObject(const EngineObject& engineObject);
		virtual ~EngineObject();

		virtual void Update() = 0;
		virtual void Draw() = 0;

		inline Ptr<Scheduler> GetScheduler() { return scheduler; }

		inline bool IsPaused() { return paused; }
		inline void Pause() { paused = true; }
		inline void Resume() { paused = false; }

		virtual void OnStart();
		virtual void OnLoad(Ptr<AsyncInfo> info);

		friend class Game;
	};
}

#endif