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

	if (position.y > 480)
	{
		MarkDestroy();
	}
}