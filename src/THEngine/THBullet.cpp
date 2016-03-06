#include "stdafx.h"
#include "THEngine.h"
#include "Effect\THFog.h"

THBullet::THBullet(int type)
{
	SetType(type);
	Init();
}

THBullet::~THBullet()
{
	for (int i = 0; i < eventNum; i++){
		TH_SAFE_DELETE(events[i]);
	}
	for (int i = 0; i < eventHandlerNum; i++){
		TH_SAFE_DELETE(eventHandlers[i]);
	}
}

void THBullet::Init(){
	EnableDetermination();
	EnableAutoDelete();
	frame = 0;
	eventNum = 0;
	eventHandlerNum = 0;
}

void THBullet::SetType(int type){
	this->type = type;
	switch (type){
		/****************Ð¡Óñ***************************/
	case SMALLJADE_RED:
		SetTexture(engine->_texBullet);
		SetImgRect(32, 48, 48, 64);
		SetFog(BULLET_FOG_RED);
		break;
	case SMALLJADE_BLUE:
		SetTexture(engine->_texBullet);
		SetImgRect(96, 48, 112, 64);
		SetFog(BULLET_FOG_BLUE);
		break;
	case SMALLJADE_PURPLE:
		SetTexture(engine->_texBullet);
		SetImgRect(64, 48, 80, 64);
		SetFog(BULLET_FOG_PURPLE);
		break;
	case SMALLJADE_TEAL:
		SetTexture(engine->_texBullet);
		SetImgRect(128, 48, 144, 64);
		SetFog(BULLET_FOG_TEAL);
		break;
	case SMALLJADE_GREEN:
		SetTexture(engine->_texBullet);
		SetImgRect(160, 48, 176, 64);
		SetFog(BULLET_FOG_GREEN);
		break;
	case SMALLJADE_YELLOW:
		SetTexture(engine->_texBullet);
		SetImgRect(192, 48, 208, 64);
		SetFog(BULLET_FOG_YELLOW);
		break;
	case SMALLJADE_ORANGE:
		SetTexture(engine->_texBullet);
		SetImgRect(224, 48, 240, 64);
		SetFog(BULLET_FOG_YELLOW);
		break;
	case SMALLJADE_GREY:
		SetTexture(engine->_texBullet);
		SetImgRect(240, 48, 256, 64);
		SetFog(BULLET_FOG_WHITE2);
		break;

		/*****************ÁÛµ¯**************/
	case SCALE_RED:
		SetTexture(engine->_texBullet);
		SetImgRect(32, 16, 48, 32);
		SetFog(BULLET_FOG_RED);
		break;
	case SCALE_BLUE:
		SetTexture(engine->_texBullet);
		SetImgRect(96, 16, 112, 32);
		SetFog(BULLET_FOG_BLUE);
		break;
	case SCALE_PURPLE:
		SetTexture(engine->_texBullet);
		SetImgRect(64, 16, 80, 32);
		SetFog(BULLET_FOG_PURPLE);
		break;
	case SCALE_TEAL:
		SetTexture(engine->_texBullet);
		SetImgRect(128, 16, 144, 32);
		SetFog(BULLET_FOG_TEAL);
		break;
	case SCALE_GREEN:
		SetTexture(engine->_texBullet);
		SetImgRect(160, 16, 176, 32);
		SetFog(BULLET_FOG_GREEN);
		break;
	case SCALE_YELLOW:
		SetTexture(engine->_texBullet);
		SetImgRect(192, 16, 208, 32);
		SetFog(BULLET_FOG_YELLOW);
		break;
	case SCALE_ORANGE:
		SetTexture(engine->_texBullet);
		SetImgRect(224, 16, 240, 32);
		SetFog(BULLET_FOG_YELLOW);
		break;
	case SCALE_GREY:
		SetTexture(engine->_texBullet);
		SetImgRect(240, 16, 256, 32);
		SetFog(BULLET_FOG_WHITE2);
		break;

	}
}

void THBullet::Update()
{
	UpdatePosition();
}

void THBullet::CommonUpdate(){
	frame++;
	if (frame <= delay){
		DisableDetermination();
	}
	else{
		EnableDetermination();
	}
	HandleEvent();
	Update();
}

int THBullet::AddEvent(THBulletEvent* e){
	if (eventNum == TH_MAX_BULLET_EVENT){
		return -1;
	}
	THBulletEvent* e2 = new THBulletEvent;
	*e2 = *e;
	events[eventNum++] = e2;
	return 0;
}

void THBullet::HandleEvent()
{
	list<THBulletEvent*>::iterator iter;
	for (int i = 0; i < eventNum; i++){
		if (events[i]->IsOccuring(frame)){
			if (events[i]->repeatTime == 0){
				TH_SAFE_DELETE(events[i]);
				for (int j = i + 1; j < eventNum; j++){
					events[j - 1] = events[j];
				}
				eventNum--;
			}
			else{
				events[i]->repeatTime--;
				if (eventHandlerNum < TH_MAX_BULLET_EVENT_HANDLER){
					BulletEventHandler* handler = CreateBulletEventHandler(events[i]);
					eventHandlers[eventHandlerNum++] = handler;
				}
			}
		}
	}
	for (int i = 0; i < eventHandlerNum; i++){
		if (eventHandlers[i]->Handle() < 0){
			TH_SAFE_DELETE(eventHandlers[i]);
			for (int j = i + 1; j < eventHandlerNum; j++){
				eventHandlers[j - 1] = eventHandlers[j];
			}
			eventHandlerNum--;
		}
	}
}

BulletEventHandler* THBullet::CreateBulletEventHandler(THBulletEvent* e)
{
	BulletEventHandler* handler = new BulletEventHandler;
	handler->attributeType = e->attributeType;
	handler->bullet = this;
	handler->changeManner = e->changeManner;
	handler->leftFrame = handler->totalFrame = e->changeTime;
	if (e->changeType == CHANGETYPE_CHANGETO){
		float src;
		switch (e->attributeType){
		case ATTRIBUTE_SPEED:
			src = this->velocity;
			break;
		}
		handler->deltaTotal = e->value - src;
	}
	else if (e->changeType == CHANGETYPE_INCREASE){
		handler->deltaTotal = e->value;
	}
	else if (e->changeType == CHANGETYPE_DECREASE){
		handler->deltaTotal = -e->value;
	}
	handler->deltaPerFrame = handler->deltaTotal / handler->totalFrame;
	return handler;
}

void THBullet::CommonDraw()
{
	Draw();
}

void THBullet::Draw()
{
	ClearTransform();
	SetRotation(x, y, angle + 90);
	if (frame > delay){
		DrawImg(x, y, 98, DRAW_CENTERED);
	}
}

bool THBullet::Hit(float x, float y, float radius){
	switch (type){
		//Ð¡Óñ
	case SMALLJADE_RED:
	case SMALLJADE_PURPLE:
	case SMALLJADE_BLUE:
	case SMALLJADE_TEAL:
	case SMALLJADE_GREEN:
	case SMALLJADE_YELLOW:
	case SMALLJADE_ORANGE:
	case SMALLJADE_GREY:
		if (sqrt((x - this->x)*(x - this->x) + (y - this->y)*(y - this->y)) <= 2.0 + radius){
			return true;
		}
		return false;

		//ÁÛµ¯
	case SCALE_RED:
	case SCALE_PURPLE:
	case SCALE_BLUE:
	case SCALE_TEAL:
	case SCALE_GREEN:
	case SCALE_YELLOW:
	case SCALE_ORANGE:
	case SCALE_GREY:
		if (fabs(x - this->x) <= 1.5 + radius && fabs(y - this->y) <= 2.5 + radius){
			return true;
		}
		return false;
	}
	return false;
}

/*void THBullet::HandleEvent(BulletEvent *e){
	if (!e->TestConditions(frame, x, y)){
		return;
	}

	float dest;
	float src;

	switch (e->AttributeType){
	case ATTRIBUTE_SPEED:
		src = this->velocity;
		break;
	case ATTRIBUTE_SPEED_DIRECTION:
		src = this->angle;
		break;
	}

	switch (e->ChangeType){
	case CHANGETYPE_CHANGETO:
		dest = e->value;
		break;
	case CHANGETYPE_INCREASE:
		dest = src + e->value;
		break;
	case CHANGETYPE_DECREASE:
		dest = src - e->value;
		break;
	}

	switch (e->AttributeType){
	case ATTRIBUTE_SPEED:
		SetVelocity(dest);
		break;
	case ATTRIBUTE_SPEED_DIRECTION:
		SetAngle(dest);
		break;
	}
}*/

/*************************BulletEventHandler****************/
BulletEventHandler::BulletEventHandler()
{

}

BulletEventHandler::~BulletEventHandler()
{

}

int BulletEventHandler::Handle()
{
	if (leftFrame == 0){
		return -1;
	}
	if (changeManner == CHANGEMANNER_LINEAR){
		switch (attributeType){
		case ATTRIBUTE_SPEED:
			bullet->velocity += deltaPerFrame;
			break;
		}
	}
	leftFrame--;
	return 0;
}
/*************************PlayerBullet**********************/
THPlayerBullet::THPlayerBullet()
{
	Init();
}

void THPlayerBullet::Init()
{
	SetAttackOnce(true);
}

void THPlayerBullet::Update()
{
}

void THPlayerBullet::Draw()
{

}

void THPlayerBullet::CommonUpdate()
{
	Update();
}

void THPlayerBullet::CommonDraw()
{
	Draw();
}