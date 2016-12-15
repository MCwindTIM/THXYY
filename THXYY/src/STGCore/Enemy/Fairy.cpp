#include "Fairy.h"
#include "../STGResources.h"

static const int ANIM_INTERVAL = 6;

Fairy::Fairy()
{
	auto STGResources = STGResources::GetInstance();

	SetTexture(STGResources->texEnemy01);

	motionState = STATIC;

	frameForAnim = 0;

	hitRange = 8.0f;
}

Fairy::~Fairy()
{

}

void Fairy::Update()
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

		SetTexRect(Rect(left, left + 32, texRect.top, texRect.bottom));

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

		SetTexRect(Rect(left, left + 32, texRect.top, texRect.bottom));
	}
}

/////////////////////////////////////////////////////////

BlueFairy01::BlueFairy01()
{
	SetTexRect(Rect(0, 32, 256, 288));

	enemyColor = BLUE;
}

BlueFairy01::~BlueFairy01()
{

}

/////////////////////////////////////////////////////////

BlueFairy02::BlueFairy02()
{
	SetTexRect(Rect(0, 32, 0, 32));

	enemyColor = BLUE;
}

BlueFairy02::~BlueFairy02()
{

}

/////////////////////////////////////////////////////////

RedFairy01::RedFairy01()
{
	SetTexRect(Rect(0, 32, 288, 320));

	enemyColor = RED;
}

RedFairy01::~RedFairy01()
{

}

/////////////////////////////////////////////////////////

RedFairy02::RedFairy02()
{
	SetTexRect(Rect(0, 32, 32, 64));

	enemyColor = RED;
}

RedFairy02::~RedFairy02()
{

}

/////////////////////////////////////////////////////////

GreenFairy01::GreenFairy01()
{
	SetTexRect(Rect(0, 32, 320, 352));

	enemyColor = GREEN;
}

GreenFairy01::~GreenFairy01()
{

}

/////////////////////////////////////////////////////////

GreenFairy02::GreenFairy02()
{
	SetTexRect(Rect(0, 32, 64, 96));

	enemyColor = GREEN;
}

GreenFairy02::~GreenFairy02()
{

}

/////////////////////////////////////////////////////////

YellowFairy01::YellowFairy01()
{
	SetTexRect(Rect(0, 32, 352, 384));

	enemyColor = YELLOW;
}

YellowFairy01::~YellowFairy01()
{

}

/////////////////////////////////////////////////////////

YellowFairy02::YellowFairy02()
{
	SetTexRect(Rect(0, 32, 96, 128));

	enemyColor = YELLOW;
}

YellowFairy02::~YellowFairy02()
{

}

/////////////////////////////////////////////////////////
