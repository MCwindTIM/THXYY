#include "PlayerBullet.h"
#include "STGEngine.h"

PlayerBullet::PlayerBullet()
{

}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Update()
{
	Sprite::Update();

	if (position.y > 512 || position.y < -64 || position.x < -64 || position.x > 448)
	{
		MarkDestroy();
	}
}