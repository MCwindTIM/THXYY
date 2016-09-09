#include "Enemy01_001.h"

Enemy01_001::Enemy01_001()
{
	frame = 0;
}

Enemy01_001::~Enemy01_001()
{

}

void Enemy01_001::Update()
{
	BlueFairy01::Update();

	auto engine = STGEngine::GetInstance();

	frame++;

	if (frame == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			int xOffset = Random(-50, 50);
			int yOffset = Random(-50, 50);

			float angle = Random(0, 17);

			for (int i = 0; i < 20; i++)
			{
				Bullet* bullet = new Bullet();
				bullet->SetType(Bullet::LINDAN_RED);
				bullet->SetPosition(position.x + xOffset, position.y + yOffset);
				bullet->SetSpeed(2);
				bullet->SetAngle(18 * i + angle);
				engine->ShootBullet(bullet);
			}
		}
		
	}

	if (frame == 25)
	{
		frame = 0;
	}
}