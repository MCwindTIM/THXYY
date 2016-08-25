#ifndef THEVENTS_H
#define THEVENTS_H

namespace THEngine
{
	class IKeyDownListener
	{
	public:
		virtual void OnKeyDown(EngineObject* sender, int key) = 0;
	};
}

#endif