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

	stgResources->soundEnemyDie00->Play();

	Particle3D* effect[10];
	for (int i = 0; i < 10; i++)
	{
		int effectLife = 40;

		effect[i] = new Particle3D();
		effect[i]->SetTexture(stgResources->texFourAngleStar);
		effect[i]->SetPosition(position);
		effect[i]->SetLife(effectLife);
		effect[i]->SetTexRect(Rect(96, 128, 32, 64));

		float effectAngle = ToRad(Random(0, 359));
		float dist = Random(0, 60);

		float effectScale = Random(4, 14) / 10.0f;
		effect[i]->SetScale(Vector3f(effectScale, effectScale, 1));

		effect[i]->SetRotatingAxis(Vector3f(Random(0, 100), Random(0, 100), Random(0, 100)));
		effect[i]->SetRotatingSpeed(Random(50, 100) / 10.0f);
		effect[i]->SetAlpha(0.6f);

		TweenSequence* sequence = new TweenSequence();
		sequence->AddTween(new Delay(effectLife / 2));
		sequence->AddTween(new ScaleTo(Vector3f(0, 0, 1), 30, Tweener::SIMPLE));
		effect[i]->AddTween(sequence);

		effect[i]->AddTween(new MoveBy(Vector3f(dist*cos(effectAngle), dist*sin(effectAngle), 0),
			effectLife, Tweener::EASE_OUT));

		engine->AddParticle(effect[i]);
	}

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

		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(64, 96, 0, 32));
		}

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

		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(0, 32, 0, 32));
		}

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

		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(0, 32, 32, 64));
		}

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

		for (int i = 0; i < 10; i++)
		{
			effect[i]->SetTexRect(Rect(32, 64, 32, 64));
		}

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

	STGResources::GetInstance()->soundDamage01->Play();
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