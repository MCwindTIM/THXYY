#include "stdafx.h"
#include "PlayerBullet.h"

ReimuBullet2::ReimuBullet2()
{
	Init();
}

void ReimuBullet2::Init(){
	texture = engine->_texPlayer;
	SetImgRect(0, 160, 32, 224);
	SetVelocity(8);
	SetAngle(-90);
	SetRange(0, 384, -10, 448);
	SetDamage(15);
}

void ReimuBullet2::Update(){
	UpdatePosition();
}

void ReimuBullet2::Draw(){
	ClearTransform();
	SetScale(x, y, 0.5, 0.5);
	DrawImg(x, y, 99, DRAW_CENTERED);
}

bool ReimuBullet2::Hit(float l, float t, float r, float b){
	if (x >= l && x <= r && y - 24 >= t && y - 24 <= b){
		return true;
	}
	return false;
}