#include "Enemy01_002.h"

Enemy01_002::Enemy01_002()
{
	life = 10;

	SetItem(POWER_SMALL, 8);
	SetItem(SCORE, 8);

	SetPosition(440, 400);
}

Enemy01_002::~Enemy01_002()
{
}

void Enemy01_002::Update()
{
	RedFairy01::Update();

	auto engine = STGEngine::GetInstance();

	frame++;

	if (frame == 5)
	{
		frame = 0;
		float bulletAngle = Random(0, 359);

		for (int i = 0; i < 3; i++)
		{
			Bullet* bullet = new Bullet();
			bullet->SetType(new BigJadeBlue());
			bullet->SetPosition(position.x, position.y);
			bullet->SetSpeed(2.5);
			bullet->SetAngle(bulletAngle + 120 * i);
			engine->ShootBullet(bullet, true, 2);
		}
	}
}