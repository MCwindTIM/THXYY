#include "Stage01.h"
#include "../Enemy/Stage01/Enemy01_001.h"

Stage01::Stage01()
{

}

Stage01::~Stage01()
{

}

void Stage01::Update()
{
	Stage::Update();

	auto engine = STGEngine::GetInstance();

	frame++;

	if (frame == 1)
	{
		Enemy01_001* enemy = new Enemy01_001();
		enemy->SetPosition(-30, 420);
		enemy->AddTween(new MoveTo(Vector3f(192, 280,enemy->GetPosition().z),180,Tweener::EASE_OUT));
		engine->AddEnemy(enemy);
	}
}

void Stage01::OnLoad()
{

}

void Stage01::UpdateBackground()
{

}