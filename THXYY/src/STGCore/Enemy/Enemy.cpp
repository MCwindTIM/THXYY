#include "Enemy.h"
#include "../STGEngine.h"
#include "../Item/PowerItemSmall.h"
#include "../Item/ScoreItem.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Sprite::Update();

	auto engine = STGEngine::GetInstance();

	auto list = engine->GetPlayerBulletList();

	auto iter = list->GetIterator();
	while (iter->HasNext())
	{
		auto playerBullet = iter->Next();
		auto playerBulletPos = playerBullet->GetPosition();
		auto difX = position.x - playerBulletPos.x;
		auto difY = position.y - playerBulletPos.y;
		auto dist = hitRange + playerBullet->GetHitRange();

		if (difX * difX + difY * difY < dist * dist)
		{
			OnHitten(playerBullet->GetDamage());
			playerBullet->MarkDestroy();
			iter->Remove();
		}
	}

	if (life < 0)
	{
		OnDie();
		MarkDestroy();
	}
}

void Enemy::OnDie()
{
	auto engine = STGEngine::GetInstance();
	auto stgResources = STGResources::GetInstance();

	engine->SetScore(engine->GetScore() + score);

	DropItems();

	switch (enemyColor)
	{
	case BLUE:
	{
		Sprite* dieEffect = new Sprite();
		dieEffect->SetPosition(position);
		dieEffect->SetTexture(stgResources->texEffBase);
		dieEffect->SetTexRect(Rect(192, 256, 16, 80));
		dieEffect->AddTween(new ScaleTo(Vector3f(2.0f, 2.0f, 1.0f), 12, Tweener::SIMPLE));
		dieEffect->AddTween(new FadeOut(12, Tweener::SIMPLE));
		engine->AddEffect(dieEffect);

		break;
	}
	case RED:
	{
		Sprite* dieEffect = new Sprite();
		dieEffect->SetPosition(position);
		dieEffect->SetTexture(stgResources->texEffBase);
		dieEffect->SetTexRect(Rect(128, 192, 16, 80));
		dieEffect->AddTween(new ScaleTo(Vector3f(2.0f, 2.0f, 1.0f), 10, Tweener::SIMPLE));
		dieEffect->AddTween(new FadeOut(10, Tweener::SIMPLE));
		engine->AddEffect(dieEffect);
		break;
	}
	case GREEN:
	{
		Sprite* dieEffect = new Sprite();
		dieEffect->SetPosition(position);
		dieEffect->SetTexture(stgResources->texEffBase);
		dieEffect->SetTexRect(Rect(64, 128, 80, 144));
		dieEffect->AddTween(new ScaleTo(Vector3f(2.0f, 2.0f, 1.0f), 10, Tweener::SIMPLE));
		dieEffect->AddTween(new FadeOut(10, Tweener::SIMPLE));
		engine->AddEffect(dieEffect);
		break;
	}
	case YELLOW:
	{
		Sprite* dieEffect = new Sprite();
		dieEffect->SetPosition(position);
		dieEffect->SetTexture(stgResources->texEffBase);
		dieEffect->SetTexRect(Rect(0, 64, 80, 144));
		dieEffect->AddTween(new ScaleTo(Vector3f(2.0f, 2.0f, 1.0f), 10, Tweener::SIMPLE));
		dieEffect->AddTween(new FadeOut(10, Tweener::SIMPLE));
		engine->AddEffect(dieEffect);
		break;
	}
		
	}
}

void Enemy::OnDestroy()
{
	
}

void Enemy::OnHitten(float damage)
{
	life -= damage;
}

void Enemy::DropItems()
{
	auto engine = STGEngine::GetInstance();

	for (int i = 0; i < powerItemSmallNum; i++)
	{
		float itemAngle = ToRad(Random(45, 135));
		float dist = Random(20, 40);

		PowerItemSmall* item = new PowerItemSmall();
		item->SetPosition(position.x,position.y);
		item->AddTween(new MoveBy(Vector3f(dist*cos(itemAngle), 
			dist*sin(itemAngle), 0), 40, Tweener::EASE_OUT));
		item->AddTween(new Rotate2D(720.0f, 40, Tweener::EASE_OUT));
		engine->AddItem(item);
	}

	for (int i = 0; i < scoreItemNum; i++)
	{
		float itemAngle = ToRad(Random(45, 135));
		float dist = Random(20, 40);

		ScoreItem* item = new ScoreItem();
		item->SetPosition(position.x, position.y);
		item->AddTween(new MoveBy(Vector3f(dist*cos(itemAngle),
			dist*sin(itemAngle), 0), 40, Tweener::EASE_OUT));
		item->AddTween(new Rotate2D(720.0f, 40, Tweener::EASE_OUT));
		engine->AddItem(item);
	}
}

void Enemy::SetItem(ItemType type, int count)
{
	switch (type)
	{
	case POWER_SMALL:
		powerItemSmallNum = count;
		break;
	case SCORE:
		scoreItemNum = count;
		break;
	}
}