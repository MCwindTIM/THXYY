#include "stdafx.h"
#include "THEvent.h"

EventCreation::~EventCreation()
{
}

void EventCreation::onEvent()
{
	//game->m_engine->m_renderlist->Add(m_obj);
}

THBulletEvent::THBulletEvent()
{

}

bool THBulletEvent::IsOccuring(int frame)
{
	if (frame < firstOccurFrame){
		return false;
	}
	if (repeatFrameInterval == 0){
		return frame == firstOccurFrame;
	}
	if ((frame - firstOccurFrame) % repeatFrameInterval == 0){
		return true;
	}
	return false;
}
