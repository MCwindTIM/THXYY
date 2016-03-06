#include "stdafx.h"
#include "THFog.h"
#include "../THCommon.h"
#include "../Engine_Core.h"

THEnemyFog::THEnemyFog(BYTE type){
	this->type = type;
	Init();
}

void THEnemyFog::Init(){
	frame = 0;
	SetTexture(engine->_texBullet2);

	int left, top, width, height;
	width = height = 64;
	left = 0;
	top = 128;

	switch (type){
	case ENEMY_FOG_RED1:
	case ENEMY_FOG_RED2:
		left = 128;
		top = 16;
		break;
	case ENEMY_FOG_GREEN1:
	case ENEMY_FOG_GREEN2:
		left = 64;
		top = 80;
		break;
	case ENEMY_FOG_BLUE1:
	case ENEMY_FOG_BLUE2:
		left = 192;
		top = 16;
		break;
	case ENEMY_FOG_YELLOW1:
	case ENEMY_FOG_YELLOW2:
		left = 0;
		top = 80;
		break;
	}
	SetImgRect(left, top, left + width, top + height);
}

void THEnemyFog::Draw(){
	ClearTransform();
	SetAlpha(1);
	switch (type){
	case ENEMY_FOG_RED1:
	case ENEMY_FOG_GREEN1:
	case ENEMY_FOG_BLUE1:
	case ENEMY_FOG_YELLOW1:
		if (frame <= 20){
			SetScale(x, y, frame * 0.1f, frame * 0.1f);
			SetAlpha(1 - frame*0.05f);
		}

		if (frame >= 20){
			MarkDelete();
		}
		break;
	case ENEMY_FOG_RED2:
	case ENEMY_FOG_GREEN2:
	case ENEMY_FOG_BLUE2:
	case ENEMY_FOG_YELLOW2:
		if (frame <= 20){
			SetScale(x, y, 1 + frame * 0.05, 0.5 - frame * 0.025);
			SetAlpha(1 - frame*0.05);
		}
		if (frame >= 20){
			MarkDelete();
		}
		break;
	}
	DrawImg(x, y, 0, DRAW_CENTERED);
}

THBulletFog::THBulletFog(BYTE type){
	this->type = type;
	Init();
}

void THBulletFog::Init(){
	frame = 0;
	SetTexture(engine->_texBullet);
	switch (type){
	case BULLET_FOG_WHITE1:
		SetImgRect(0, 208, 32, 240);
		break;
	case BULLET_FOG_RED:
		SetImgRect(32, 208, 64, 240);
		break;
	case BULLET_FOG_PURPLE:
		SetImgRect(64, 208, 96, 240);
		break;
	case BULLET_FOG_BLUE:
		SetImgRect(96, 208, 128, 240);
		break;
	case BULLET_FOG_TEAL:
		SetImgRect(128, 208, 160, 240);
		break;
	case BULLET_FOG_GREEN:
		SetImgRect(160, 208, 192, 240);
		break;
	case BULLET_FOG_YELLOW:
		SetImgRect(192, 208, 224, 240);
		break;
	case BULLET_FOG_WHITE2:
		SetImgRect(224, 208, 256, 240);
		break;
	}
}

void THBulletFog::Draw(){
	ClearTransform();
	if (frame <= 10){
		SetScale(x, y, 0.2f*frame, 0.2f*frame);
		SetAlpha(1 - 0.1f*frame);
	}
	if (frame >= 10){
		MarkDelete();
	}
	DrawImg(x, y, 1, DRAW_CENTERED);
}