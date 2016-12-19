#include "ButterFly.h"
#include "../STGResources.h"

ButterFly::ButterFly()
{
	auto STGResources = STGResources::GetInstance();

	SetTexture(STGResources->texEnemy01);

	SetTexRect(Rect(0, 64, 384, 448));

	hitRange = 8.0f;
}

ButterFly::~ButterFly()
{

}

void ButterFly::Update()
{
	Enemy::Update();

	int left;
	int period = frameForAnim / ANIM_INTERVAL;

	switch (motionState)
	{
	case STATIC:
		left = period * 64;
		SetTexRect(Rect(left, left + 64, 384, 448));
		break;
	case STATIC_TO_LEFT:
		left = period * 64 + 256;
		SetTexRect(Rect(left, left + 64, 384, 448));
		SetFlipX(true);
		break;
	case STATIC_TO_RIGHT:
		left = period * 64 + 256;
		SetTexRect(Rect(left, left + 64, 384, 448));
		break;
	case LEFT_TO_STATIC:
		left = 448 - period * 64;
		SetTexRect(Rect(left, left + 64, 384, 448));
		SetFlipX(true);
		break;
	case RIGHT_TO_STATIC:
		left = 448 - period * 64;
		SetTexRect(Rect(left, left + 64, 384, 448));
		break;
	case LEFT:
	case RIGHT:
		if (period < 2)
		{
			left = 384 + 64 * period;
			SetTexRect(Rect(left, left + 64, 256, 320));
		}
		else
		{
			left = 256 + 64 * period;
			SetTexRect(Rect(left, left + 64, 320, 384));
		}
		if (motionState == LEFT)
		{
			SetFlipX(true);
		}
	default:
		break;
	}
}