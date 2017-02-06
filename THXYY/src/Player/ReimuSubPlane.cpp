#include "ReimuSubPlane.h"

const float ReimuSubPlane::ROTATION_SPEED = 6.0f;

ReimuSubPlane::ReimuSubPlane()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texReimu);
	SetTexRect(Rect(80, 96, 144, 160));
}

ReimuSubPlane::~ReimuSubPlane()
{

}

void ReimuSubPlane::Update()
{
	Sprite::Update();

	this->rotation += ROTATION_SPEED;
}
