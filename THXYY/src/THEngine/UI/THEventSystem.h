#ifndef THEVENTSYSTEM_H
#define THEVENTSYSTEM_H

#include "../Common/THCommon.h"
#include "THEvents.h"
#include <list>

namespace THEngine
{
	class EventSystem : public Object
	{
	private:
		EventSystem();
		static EventSystem* instance;

	protected:
		std::list<IKeyDownListener*> keyDownListeners;

	public:
		~EventSystem();

		static EventSystem* Create();

		static EventSystem* GetInstance();

		void OnKeyDown(int key);

		void RegisterKeyDownListener(IKeyDownListener* listener);
		void UnRegisterKeyDownListener(IKeyDownListener* listener);
	};
}

#endif