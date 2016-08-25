#include "THEventSystem.h"

using namespace THEngine;

EventSystem* EventSystem::instance = nullptr;

EventSystem::EventSystem()
{

}

EventSystem::~EventSystem()
{

}

EventSystem* EventSystem::Create()
{
	if (instance == nullptr)
	{
		instance = new EventSystem();
		instance->Retain();
		return instance;
	}
	return nullptr;
}

EventSystem* EventSystem::GetInstance()
{
	return instance;
}

void EventSystem::OnKeyDown(int key)
{
	auto iter = keyDownListeners.begin();
	for (; iter != keyDownListeners.end(); iter++)
	{
		auto listener = *iter;
		listener->OnKeyDown(nullptr, key);
	}
}

void EventSystem::RegisterKeyDownListener(IKeyDownListener* listener)
{
	keyDownListeners.push_back(listener);
}

void EventSystem::UnRegisterKeyDownListener(IKeyDownListener* listener)
{
	keyDownListeners.remove(listener);
}