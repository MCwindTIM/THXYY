#include "Enemy.h"
#include "../STGEngine.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Sprite::Update();

	if (life < 0)
	{
		OnDie();
		MarkDestroy();
	}
}

void Enemy::OnDie()
{
	auto engine = STGEngine::GetInstance();

	engine->SetScore(engine->GetScore() + score);
}

void Enemy::OnDestroy()
{
	
}