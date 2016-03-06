#include "stdafx.h"
#include "Player.h"
#include "PlayerBullet.h"

Reimu::Reimu()
{
	Init();
}

void Reimu::Init(){
	h_velocity = 10.0f / 3;
	l_velocity = 1.5;
	r = 2.25;
	h_step = (float)h_velocity;
	h_step2 = h_step * 0.7f;
	l_step = (float)l_velocity;
	l_step2 = l_step * 0.7f;
	texture = engine->_texPlayer;
	fireframe = 0;
	power = 0;
	maxpower = 400;
}

void Reimu::Update()
{
	if (fireframe > 0){
		fireframe--;
	}
	THPlayer::Update();
}

void Reimu::Draw()
{
	if (frame > 60){
		if (direction == DIRECTION_STABLE){
			frame = 0;
		}
		else{
			frame = 16;
		}
	}

	ClearTransform();
	RECT rc;
	if (direction == DIRECTION_LEFT || direction == DIRECTION_LEFT_AND_UP || direction == DIRECTION_LEFT_AND_DOWN){
		rc.top = 48;
		rc.bottom = 96;
	}
	else if (direction == DIRECTION_RIGHT || direction == DIRECTION_RIGHT_AND_UP || direction == DIRECTION_RIGHT_AND_DOWN){
		rc.top = 48;
		rc.bottom = 96;
		SetReversalX(x);
	}
	else{
		rc.top = 0;
		rc.bottom = 48;
	}

	if (frame <= 15){
		rc.left = 0;
		rc.right = 32;
	}
	else if (frame <= 30){
		rc.left = 32;
		rc.right = 64;
	}
	else if (frame <= 45){
		rc.left = 64;
		rc.right = 96;
	}
	else{
		rc.left = 96;
		rc.right = 128;
	}
	SetImgRect(rc.left, rc.top, rc.right, rc.bottom);
	DrawImg(x, y, 99, DRAW_CENTERED);

	if (!bHigh){   //»æÖÆÅÐ¶¨µã
		RECT rc;
		rc.left = 0;
		rc.right = 64;
		rc.top = 16;
		rc.bottom = 80;

		SetScale(x, y, 1, 1);
		SpriteDraw(engine->_texBullet2, rc.left, rc.top, rc.right, rc.bottom, x - 32, y - 32, 0);
	}
}

void Reimu::Fire()
{
	if (fireframe == 0){
		ReimuBullet2 *bullet = new ReimuBullet2;
		CreatePlayerBullet(bullet, x, y);
		fireframe = 10;
	}
}