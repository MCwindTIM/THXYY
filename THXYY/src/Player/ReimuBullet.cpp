#include "ReimuBullet.h"

ReimuBullet::ReimuBullet()
{
	auto stgResources = STGResources::GetInstance();

	SetDamage(14.0f);
	SetAngle(90.0f);
	SetSpeed(30.0f);
	SetTexture(stgResources->texReimu);
	SetTexRect(Rect(200, 256, 144, 160));
	SetRotation(90.0f);
	SetHitRange(15.0f);
}

ReimuBullet::~ReimuBullet()
{

}