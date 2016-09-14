#include "ScoreItem.h"
#include "../STGResources.h"
#include "../STGEngine.h"

ScoreItem::ScoreItem()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texEffBase);
	SetTexRect(Rect(16, 32, 208, 224));

	hitRange = 8.0f;
}

ScoreItem::~ScoreItem()
{

}

void ScoreItem::OnGot()
{
	Item::OnGot();

	auto engine = STGEngine::GetInstance();
	auto player = engine->GetPlayer();
	float yPlayer = player->GetPosition().y;

	if (gotFromHigh)
	{
		engine->SetScore(engine->GetScore() + engine->GetMaxPoint());
	}
	else
	{
		int add = yPlayer / player->GetItemGetHeight() * engine->GetMaxPoint();
		add /= 10;
		add *= 10;
		engine->SetScore(engine->GetScore() + add);
	}
}

