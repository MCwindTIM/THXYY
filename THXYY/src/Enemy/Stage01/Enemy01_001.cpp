#include "Enemy01_001.h"

Enemy01_001::Enemy01_001()
{
	frame = 0;
	life = 10;

	SetItem(POWER_SMALL, 8);
	SetItem(SCORE, 8);
}

Enemy01_001::~Enemy01_001()
{
}

void Enemy01_001::Update()
{
	BlueFairy01::Update();

	auto engine = STGEngine::GetInstance();

	frame++;

	if (frame == 2)
	{
		frame = 0;

		shootAngle += acShootAngle;

		for (int i = 0; i < 5; i++)
		{
			Bullet* bullet = new Bullet();
			bullet->SetType(new ArrowTeal());
			bullet->SetPosition(position.x, position.y);
			bullet->SetSpeed(2.5);
			bullet->SetAngle(72 * i + shootAngle);

			engine->ShootBullet(bullet, true, 2);
		}

		acShootAngle += 0.08f;
	}
}