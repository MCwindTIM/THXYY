#include "stdafx.h"
#include "THMaple.h"

void THMaple::Init(){
	frame = 0;
	SetTexture(engine->_texBullet2);
	SetImgRect(32, 224, 64, 256);
}

void THMaple::Update()
{
	frame++;
	switch (this->RotationDir){
	case ROTATION_CLOCKWISE:
		rot += vRotation;
		break;
	case ROTATION_ANTICLOCKWISE:
		rot -= vRotation;
		break;
	}

	UpdatePosition();
	if (frame >= life){
		MarkDelete();
	}
}

void THMaple::Draw()
{
	ClearTransform();
	SetRotation(x, y, rot);
	SetAlpha(0.5 - 0.5*(float)frame / life);
	switch (type){
	case MAPLE_DEFAULT:
		DrawImg(x, y, 0, DRAW_CENTERED);
		break;
	case MAPLE_RED:
		DrawImg(x, y, 0, DRAW_CENTERED, 255, 0, 0);
		break;
	case MAPLE_GREEN:
		DrawImg(x, y, 0, DRAW_CENTERED, 0, 255, 0);
		break;
	case MAPLE_BLUE:
		DrawImg(x, y, 0, DRAW_CENTERED, 0, 0, 255);
		break;
	case MAPLE_YELLOW:
		DrawImg(x, y, 0, DRAW_CENTERED, 255, 255, 0);
		break;
	}
}