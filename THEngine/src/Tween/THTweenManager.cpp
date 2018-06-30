#include "THTweenManager.h"

namespace THEngine
{
	TweenManager::TweenManager()
	{

	}

	TweenManager::TweenManager(const TweenManager& tweenManager) : Object(tweenManager)
	{
		auto iter = const_cast<TweenManager&>(tweenManager).tweenList.GetIterator();
		while (iter->HasNext())
		{
			auto tween = iter->Next();
			AddTween((Tween*)tween->Clone().Get());
		}
	}

	TweenManager::~TweenManager()
	{

	}

	void TweenManager::Update()
	{
		auto iter = tweenList.GetIterator();
		while (iter->HasNext())
		{
			auto tween = iter->Next();
			tween->Update();
			if (tween->finished)
			{
				iter->Remove();
			}
		}
	}
}