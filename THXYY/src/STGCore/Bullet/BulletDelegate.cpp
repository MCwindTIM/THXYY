#include "Bullet.h"
#include "BulletDelegate.h"
#include "../stgResources.h"

bool LinDan::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer, yPlayer);

	playerCenter = playerCenter - Vector2f(bullet->GetPosition().x, bullet->GetPosition().y - 3);
	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());

	return (fabs(playerCenter.x) < 1.0f + radius) && (fabs(playerCenter.y) < 1.0f + radius);
}