#include "Fairy.h"
#include "../STGResources.h"

Fairy::Fairy()
{
	auto STGResources = STGResources::GetInstance();

	SetTexture(STGResources->texEnemy01);

	motionState = STATIC;

	hitRange = 8.0f;
}

Fairy::~Fairy()
{

}

void Fairy::Update()
{
	Enemy::Update();

	int left;

	switch (motionState)
	{
	case STATIC:
		left = frameForAnim / ANIM_INTERVAL * 32;
		break;
	case STATIC_TO_LEFT:
		left = frameForAnim / ANIM_INTERVAL * 32 + 128;
		SetFlipX(true);
		break;
	case STATIC_TO_RIGHT:
		left = frameForAnim / ANIM_INTERVAL * 32 + 128;
		break;
	case LEFT_TO_STATIC:
		left = 224 - frameForAnim / ANIM_INTERVAL * 32;
		SetFlipX(true);
		break;
	case RIGHT_TO_STATIC:
		left = 224 - frameForAnim / ANIM_INTERVAL * 32;
		break;
	case LEFT:
		left = frameForAnim / ANIM_INTERVAL * 32 + 256;
		SetFlipX(true);
		break;
	case RIGHT:
		left = frameForAnim / ANIM_INTERVAL * 32 + 256;
		break;
	default:
		break;
	}
	
	SetTexRect(Rect(left, left + 32, texRect.top, texRect.bottom));
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
