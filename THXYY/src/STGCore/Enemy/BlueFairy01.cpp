#include "BlueFairy01.h"
#include "../STGResources.h"

static const int ANIM_INTERVAL = 6;

BlueFairy01::BlueFairy01()
{
	auto STGResources = STGResources::GetInstance();

	SetTexture(STGResources->texEnemy01);

	motionState = STATIC;

	frameForAnim = 0;
}

BlueFairy01::~BlueFairy01()
{

}

void BlueFairy01::Update()
{
	Enemy::Update();

	frameForAnim++;

	if (fabs(speed) < 1e-2)
	{
		if (motionState == LEFT || motionState == RIGHT)
		{

		}
		motionState = STATIC;

		int left = frameForAnim / ANIM_INTERVAL * 32;

		SetTexRect(Rect(left, left + 32, 256, 288));

		if (frameForAnim >= 4 * ANIM_INTERVAL)
		{
			frameForAnim = 0;
		}
	}

	else 
	{
		if (vx < 0)
		{
			SetFlipX(true);
		}
		else
		{
			SetFlipX(false);
		}
		if (motionState == STATIC)
		{
			frameForAnim = 0;

			motionState = LEFT;
		}

		if (frameForAnim >= 8 * ANIM_INTERVAL)
		{
			frameForAnim = 4 * ANIM_INTERVAL;
		}

		int left = frameForAnim / ANIM_INTERVAL * 32 + 128;

		SetTexRect(Rect(left, left + 32, 256, 288));
	}
}