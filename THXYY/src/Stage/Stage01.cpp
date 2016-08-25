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


}

void Stage01::OnLoad()
{
	auto engine = STGEngine::GetInstance();

	Enemy01_001* enemy = new Enemy01_001();
	enemy->SetPosition(300, 300);
	engine->AddEnemy(enemy);
}

void Stage01::UpdateBackground()
{

}