#include "THRenderQueue.h"
#include "THRenderer.h"
#include "../Core/THGame.h"
#include <iostream>

using namespace THEngine;

void RenderQueue::Add(GameObject* obj)
{
	objList.Add(obj);
}

void RenderQueue::Render()
{
	auto iter = objList.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->Draw();
	}
}

void RenderQueue::Clear()
{
	objList.Clear();
}

/////////////////////////////////////////////

bool SpriteRenderQueue::Compare(GameObject* sprite1, GameObject* sprite2)
{
	/*Sprite* sp1 = (Sprite*)sprite1;
	Sprite* sp2 = (Sprite*)sprite1;
	if (sp1->GetPosition().z != sp2->GetPosition().z)
	{
		return sp1->GetPosition().z > sp2->GetPosition().z;
	}
	return sp1->GetTexture() > sp2->GetTexture();*/
	return sprite1->GetPosition().z > sprite2->GetPosition().z;
}

void SpriteRenderQueue::Render()
{
	SpriteRenderer* renderer = Game::GetInstance()->GetSpriteRenderer();

	objList.Sort(0, objList.Size(), SpriteRenderQueue::Compare);

	auto iter = objList.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->Draw();
	}
}

void SpriteRenderQueue::Add(GameObject* obj)
{
	objList.Add(obj);
}

/////////////////////////////////////////////
NormalRenderQueue::NormalRenderQueue()
{

}

NormalRenderQueue::~NormalRenderQueue()
{

}