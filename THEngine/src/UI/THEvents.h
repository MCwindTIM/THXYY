#ifndef TH_EVENTS_H
#define TH_EVENTS_H

namespace THEngine
{
	class IKeyDownListener
	{
	public:
		virtual bool OnKeyDown(Ptr<EngineObject> sender, int key) = 0;
	};
}

#endif