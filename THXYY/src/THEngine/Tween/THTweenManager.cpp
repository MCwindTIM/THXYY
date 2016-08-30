#include "THTweenManager.h"
#include "THTween.h"

namespace THEngine
{
	TweenManager::TweenManager()
	{

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