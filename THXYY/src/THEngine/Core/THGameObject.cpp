#include "THGameObject.h"

using namespace THEngine;

GameObject::GameObject()
{
	needRemove = false;
}

GameObject::~GameObject()
{

}

void GameObject::AddChild(GameObject* obj)
{
	children.Add(obj);
}

void GameObject::Visit()
{
	SendToRenderQueue();
	Iterator<GameObject*>* iter = children.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->Visit();
	}
}

void GameObject::Update()
{
	Iterator<GameObject*>* iter = children.GetIterator();
	while (iter->HasNext())
	{
		auto obj = iter->Next();
		if (obj->needRemove)
		{
			obj->OnDestroy();
			iter->Remove();
		}
		else
		{
			obj->Update();
		}
	}
}

void GameObject::Draw()
{

}

void GameObject::SendToRenderQueue()
{

}

void GameObject::OnDestroy()
{

}

void GameObject::RemoveChild(GameObject* child)
{
	auto iter = children.GetIterator();
	while (iter->HasNext())
	{
		auto curChild = iter->Next();
		if (curChild == child)
		{
			iter->Remove();
			return;
		}
		curChild->RemoveChild(child);
	}
}

