#include "Enemy01_003.h"

Enemy01_003::Enemy01_003()
{

}

Enemy01_003::~Enemy01_003()
{

}

void Enemy01_003::Update()
{
	ButterFly::Update();

	frame++;

	if (speed < 0)
	{
		SetAcSpeed(0);
		SetSpeed(0);
	}
}