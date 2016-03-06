#include "stdafx.h"
#include "THItem.h"
#include "THCommon.h"
#include "Engine_Core.h"

THItem::THItem()
{
	Init();
}

void THItem::Init()
{
	SetAngle(90);
	SetVelocity(-1);
	SetAcceleration((float)1 / 30);
	SetVelocityRange(-1, 2.5);
}

void THItem::Update()
{
	UpdatePosition();
}

void THItem::Draw()
{
	ClearTransform();
	DrawImg(x, y, 50, DRAW_CENTERED);
}

void THItem::CommonUpdate()
{
	Update();
	if (Hit(GetPlayerX(), GetPlayerY())){
		MarkDelete();
		Effect();
	}
}

void THItem::CommonDraw()
{
	Draw();
}

bool THItem::Hit(float x, float y){
	return false;
}

PowerItemSmall::PowerItemSmall()
{
	Init();
}

void PowerItemSmall::Init()
{
	SetTexture(engine->_texItem);
	SetImgRect(192, 0, 208, 16);
	SetRange(-8, 392, -8, 456);
}

void PowerItemSmall::Update()
{
	THItem::Update();
}

void PowerItemSmall::Draw()
{
	THItem::Draw();
}

bool PowerItemSmall::Hit(float x, float y)
{
	if (this->x >= x - 12 && this->x <= x + 12
		&& this->y >= y - 18 && this->y <= y + 18){
		return true;
	}
	return false;
}

void PowerItemSmall::Effect()
{
	SetPlayerPower(GetPlayerPower() + 1);
}