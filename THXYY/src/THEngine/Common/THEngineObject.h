#ifndef THENGINEOBJECT_H
#define THENGINEOBJECT_H

#include "THObject.h"
#include "THScheduler.h"

namespace THEngine
{
	class EngineObject : public Object
	{
	protected:
		Scheduler* scheduler;

	public:
		EngineObject();
		virtual ~EngineObject();

		virtual void Update() = 0;
		virtual void Draw() = 0;

		inline Scheduler* GetScheduler() { return scheduler; }
	};
}

#endif