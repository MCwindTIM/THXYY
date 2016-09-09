#include "Bullet.h"
#include "LinDan.h"
#include "../stgResources.h"

Texture* LinDan::GetTexture()
{
	return STGResources::GetInstance()->texBullet01;
}

bool LinDan::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer, yPlayer);

	playerCenter = playerCenter - Vector2f(bullet->GetPosition().x, bullet->GetPosition().y - 3);
	playerCenter = Rotate2D(playerCenter, -bullet->GetRotation());

	return (fabs(playerCenter.x) < 1.0f + radius) && (fabs(playerCenter.y) < 1.0f + radius);
}

Rect LinDanRed::GetTexRect()
{
	return Rect(16, 32, 16, 32);
}

Bullet::BulletColor LinDanRed::GetBulletColor()
{
	return RED;
}