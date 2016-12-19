#include "Bullet.h"
#include "BulletDelegate.h"
#include "../stgResources.h"

bool LinDan::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());

	playerCenter.y += 3;

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool SmallJade::Hit(float xPlayer, float yPlayer, float radius)
{
	float r = radius + 1.0f;

	float x = xPlayer - bullet->GetPosition().x;
	float y = yPlayer - bullet->GetPosition().y;

	return (x*x + y*y) < r*r;
}

bool Chain::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());

	playerCenter.y -= 3;

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool Rice::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool ChongDan::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());

	playerCenter.y -= 1;

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool ZhaDan::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());

	return (fabs(playerCenter.x) < radius) && (fabs(playerCenter.y) < radius);
}

bool Bacilli::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool StarBulletSmall::Hit(float xPlayer, float yPlayer, float radius)
{
	float r = radius + 2.0f;

	float x = xPlayer - bullet->GetPosition().x;
	float y = yPlayer - bullet->GetPosition().y;

	return (x*x + y*y) < r*r;
}

bool PointBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool NeedleBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool BacteriaBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	return playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y < radius * radius;
}

bool StarBulletBig::Hit(float xPlayer, float yPlayer, float radius)
{
	float r = radius + 3.0f;

	float x = xPlayer - bullet->GetPosition().x;
	float y = yPlayer - bullet->GetPosition().y;

	return (x*x + y*y) < r*r;
}

bool MidJade::Hit(float xPlayer, float yPlayer, float radius)
{
	float r = radius + 5.0f;

	float x = xPlayer - bullet->GetPosition().x;
	float y = yPlayer - bullet->GetPosition().y;

	return (x*x + y*y) < r*r;
}

bool ButterflyBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());

	playerCenter.x -= 0.5f;
	playerCenter.y -= 0.5f;

	float r = radius + 1.0f;

	return (playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y) < r*r;
}

bool KnifeBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());

	playerCenter.y -= 2;

	return (fabs(playerCenter.x) < radius + 1) && (fabs(playerCenter.y) < radius + 4);
}

bool EllipseBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	float r = radius + 2.0f;

	float x = xPlayer - bullet->GetPosition().x;
	float y = yPlayer - bullet->GetPosition().y;

	return (x*x + y*y) < r*r;
}

bool DiDan::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());
	playerCenter.y -= 1;

	float r = radius;

	return (playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y) < r*r;
}

bool HeartBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	float r = radius + 5.0f;

	return (playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y) < r*r;
}

bool ArrowBullet::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	playerCenter = VecRotate2D(playerCenter, -bullet->GetRotation());
	playerCenter.y -= 8.0f;

	return (playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y) < radius * radius;
}

bool BigJade::Hit(float xPlayer, float yPlayer, float radius)
{
	Vector2f playerCenter(xPlayer - bullet->GetPosition().x, yPlayer - bullet->GetPosition().y);

	float r = radius + 13.0f;

	return (playerCenter.x * playerCenter.x + playerCenter.y * playerCenter.y) < r * r;
}