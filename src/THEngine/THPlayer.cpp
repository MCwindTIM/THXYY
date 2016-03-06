#include "stdafx.h"
#include "THCommon.h"
#include "THPlayer.h"
#include "Effect\THBiuEffect.h"
#include <math.h>

THPlayer::THPlayer()
{
	Init();
}

THPlayer::~THPlayer()
{

}

void THPlayer::Init()
{
	frame = deadframe = 0;
	x = 192;
	y = 360;
	direction = DIRECTION_STABLE;
	bHigh = true;
	SetDead(false);
	EnableDamage();
}

void THPlayer::Update()
{
	frame++;
	if (IsDead()){
		deadframe++;
		if (deadframe>30){
			Reset();
			return;
		}
		SetAlpha(1.0f - (float)deadframe / 30.0f);
		return;
	}
	if (bHigh){
		SetVelocity(h_velocity);
	}
	else{
		SetVelocity(l_velocity);
	}
	switch (direction){
	case DIRECTION_LEFT:
		SetAngle(180);
		break;
	case DIRECTION_RIGHT:
		SetAngle(0);
		break;
	case DIRECTION_UP:
		SetAngle(-90);
		break;
	case DIRECTION_DOWN:
		SetAngle(90);
		break;
	case DIRECTION_LEFT_AND_UP:
		SetAngle(-135);
		break;
	case DIRECTION_LEFT_AND_DOWN:
		SetAngle(135);
		break;
	case DIRECTION_RIGHT_AND_UP:
		SetAngle(-45);
		break;
	case DIRECTION_RIGHT_AND_DOWN:
		SetAngle(45);
		break;
	default:
		SetVelocity(0);
		break;
	}
	UpdatePosition();

	if (x < 16)   x = 16;
	if (x > 368)  x = 368;
	if (y < 18)   y = 18;
	if (y > 430)  y = 430;
}

void THPlayer::Draw()
{
}

void THPlayer::SetPlayerDirection(UINT direction){
	this->direction = direction;
}

void THPlayer::Biu()
{
	SetDead(true);
	deadframe = 0;
	DisableDamage();

	THBiuEffect1* biuEffect1 = new THBiuEffect1;
	biuEffect1->SetPosition(x, y);
	AddRenderObject(biuEffect1);
}

void THPlayer::Reset()
{
	frame = deadframe = 0;
	SetPosition(192, 360);
	SetDead(false);
	bHigh = true;
	SetAlpha(1.0);
	EnableDamage();
}