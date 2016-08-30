#include "THConcreteTween.h"
#include "THConcreteTweener.h"
#include "../Core/THRenderObject.h"

namespace THEngine
{
	MoveTo::MoveTo(Vector3f  position, int duration, Tweener::Type type)
	{
		this->position = position;
		this->duration = duration;
		this->type = type;
	}

	MoveTo::~MoveTo()
	{

	}

	void MoveTo::OnStart()
	{
		TweenUnit::OnStart();

		TH_SAFE_RELEASE(tweener);
		tweener = new Vector3fTweener(&object->position, object->position, position, duration, type);
		tweener->Retain();
	}

	////////////////////////////////////////////////////
	MoveBy::MoveBy(Vector3f  position, int duration, Tweener::Type type)
	{
		this->position = position;
		this->duration = duration;
		this->type = type;
	}

	MoveBy::~MoveBy()
	{

	}

	void MoveBy::OnStart()
	{
		TweenUnit::OnStart();

		TH_SAFE_RELEASE(tweener);
		tweener = new Vector3fTweener(&object->position, object->position, object->position + position, duration, type);
		tweener->Retain();
	}

	/////////////////////////////////////////////////////////
	FadeTo::FadeTo(float alpha, int duration, Tweener::Type type)
	{
		this->alpha = alpha;
		this->duration = duration;
		this->type = type;
	}

	FadeTo::~FadeTo()
	{

	}

	void FadeTo::OnStart()
	{
		TweenUnit::OnStart();

		TH_SAFE_RELEASE(tweener);
		tweener = new FloatTweener(&object->alpha, object->alpha, alpha, duration, type);
		tweener->Retain();
	}

	/////////////////////////////////////////////////////////
	FadeOut::FadeOut(int duration, Tweener::Type type)
	{
		this->duration = duration;
		this->type = type;
	}

	FadeOut::~FadeOut()
	{

	}

	void FadeOut::OnStart()
	{
		TweenUnit::OnStart();

		TH_SAFE_RELEASE(tweener);
		tweener = new FloatTweener(&object->alpha, object->alpha, 0, duration, type);
		tweener->Retain();
	}

	void FadeOut::OnFinish()
	{
		TweenUnit::OnFinish();

		object->MarkDestroy();
	}

	///////////////////////////////////////////////////////////
	ColorTo::ColorTo(Vector3f color, int duration, Tweener::Type type)
	{
		this->color = color;
		this->duration = duration;
		this->type = type;
	}

	ColorTo::~ColorTo()
	{

	}

	void ColorTo::OnStart()
	{
		TweenUnit::OnStart();

		TH_SAFE_RELEASE(tweener);
		tweener = new Vector3fTweener(&object->color, object->color, color, duration, type);
		tweener->Retain();
	}
}