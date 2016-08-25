#include "Bullet.h"
#include "LinDan.h"
#include "../STGEngine.h"

BulletDelegate::BulletDelegate(Bullet* bullet)
{
	this->bullet = bullet;
}

BulletDelegate::~BulletDelegate()
{

}

////////////////////   Bullet    //////////////////////

Bullet::Bullet()
{
	bulletDelegate = nullptr;

	dirSame = true;
}

Bullet::~Bullet()
{
	TH_SAFE_RELEASE(bulletDelegate);
}

void Bullet::Update()
{	
	Sprite::Update();

	auto engine = STGEngine::GetInstance();

	auto player = engine->GetPlayer();
	if (player->IsInvincible())
	{
		if (Hit(player->GetPosition().x, player->GetPosition().y, player->GetRadius()))
		{
			MarkDestroy();
		}
	}
	else if (player->IsDamageable())
	{
		if (Hit(player->GetPosition().x, player->GetPosition().y, player->GetRadius()))
		{
			player->Hitten();
			MarkDestroy();
		}
	}

	if (dirSame)
	{
		SetRotation(angle - 90);
	}

	if (autoDelete)
	{
		if (position.x < -32 || position.x > 416 || position.y < -32 || position.y > 480)
		{
			MarkDestroy();
		}
	}
}

void Bullet::SetType(Type type)
{
	switch (type)
	{
	case LINDAN_RED:
		bulletDelegate = new LinDanRed(this);
		bulletDelegate->Retain();
		break;
	}

	if (bulletDelegate)
	{
		SetTexture(bulletDelegate->GetTexture());
		SetTexRect(bulletDelegate->GetTexRect());
		SetBulletColor(bulletDelegate->GetBulletColor());
	}
}