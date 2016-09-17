#include "THRenderObject.h"
#include "../Tween/THConcreteTween.h"

namespace THEngine
{
	RenderObject::RenderObject()
	{
		tweenManager = new TweenManager();
		tweenManager->Retain();

		D3DXQuaternionIdentity(&rotation3D);
	}

	RenderObject::~RenderObject()
	{
		TH_SAFE_RELEASE(tweenManager);
	}

	void RenderObject::Update()
	{
		GameObject::Update();
		tweenManager->Update();
	}

	void RenderObject::AddTween(Tween* tween)
	{
		tween->Bind(this);
		tweenManager->AddTween(tween);
	}
}