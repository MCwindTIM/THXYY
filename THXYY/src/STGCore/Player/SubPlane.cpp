#include "SubPlane.h"

SubPlane::SubPlane()
{

}

SubPlane::~SubPlane()
{

}

void SubPlane::Update()
{
	Sprite::Update();
}

void SubPlane::Disappear()
{
	ClearTweens();

	ScaleTo* scaleTo = new ScaleTo(Vector3f(0, 0, 1), 16, Tweener::SIMPLE);
	scaleTo->onFinished = [this](){
		this->MarkDestroy();
	};
	AddTween(scaleTo);
}