#include "THTween.h"

namespace THEngine
{
	Tween::Tween()
	{

	}

	Tween::~Tween()
	{
		
	}

	void Tween::Update()
	{
		if (started == false)
		{
			OnStart();
		}

		if (finished == false)
		{
			DoTween();
		}
	}

	void Tween::DoTween()
	{

	}

	void Tween::OnReset()
	{
		started = false;
		finished = false;
	}

	void Tween::OnStart()
	{
		started = true;
	}

	void Tween::OnFinish()
	{
		finished = true;
		onFinished();
	}


	void Tween::Bind(RenderObject* object)
	{
		this->object = object;
	}

	////////////////////////////////////////
	TweenUnit::TweenUnit()
	{

	}

	TweenUnit::~TweenUnit()
	{
		TH_SAFE_RELEASE(tweener);
	}

	void TweenUnit::DoTween()
	{
		if (tweener)
		{
			tweener->Update();
			if (tweener->elapsed == tweener->duration)
			{
				if (looped)
				{
					OnReset();
				}
				else
				{
					OnFinish();
				}
			}
		}
	}

	void TweenUnit::OnReset()
	{
		Tween::OnReset();

		TH_SAFE_RELEASE(tweener);
	}

	////////////////////////////////////////
	TweenSequence::TweenSequence()
	{
		tweenList.SetBaseSize(5);
	}

	TweenSequence::~TweenSequence()
	{

	}

	void TweenSequence::DoTween()
	{
		auto tween = tweenList.Get(currentIndex);
		
		tween->Update();

		if (tween->IsFinished())
		{
			if (currentIndex + 1 < tweenList.Size())
			{
				currentIndex++;
			}
			else
			{
				if (looped)
				{
					OnReset();
				}
				else
				{
					OnFinish();
				}
			}
		}
	}

	void TweenSequence::OnStart()
	{
		Tween::OnStart();

		if (tweenList.Size() == 0)
		{
			OnFinish();
			return;
		}
	}

	void TweenSequence::OnReset()
	{
		currentIndex = 0;

		auto iter = tweenList.GetIterator();
		while (iter->HasNext())
		{
			iter->Next()->OnReset();
		}
	}

	void TweenSequence::Bind(RenderObject* object)
	{
		Tween::Bind(object);

		auto iter = tweenList.GetIterator();
		while (iter->HasNext())
		{
			iter->Next()->Bind(object);
		}
	}
}
