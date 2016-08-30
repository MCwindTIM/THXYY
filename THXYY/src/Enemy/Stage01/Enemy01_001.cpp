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
		Bullet* bullet = new Bullet();
		bullet->SetType(Bullet::LINDAN_RED);
		bullet->SetPosition(position.x, position.y);
		bullet->SetSpeed(3);
		bullet->SetAngle(-90);
		engine->ShootBullet(bullet);
	}

	if (frame == 25)
	{
		frame = 0;
	}
}