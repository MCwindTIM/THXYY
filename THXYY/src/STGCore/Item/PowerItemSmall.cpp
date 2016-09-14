#include "PowerItemSmall.h"
#include "../STGResources.h"
#include "../STGEngine.h"

PowerItemSmall::PowerItemSmall()
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texEffBase);
	SetTexRect(Rect(0, 16, 208, 224));

	hitRange = 8.0f;
}

PowerItemSmall::~PowerItemSmall()
{

}

void PowerItemSmall::OnGot()
{
	Item::OnGot();

	auto engine = STGEngine::GetInstance();

	auto power = engine->GetPower();
	if (power < 400)
	{
		engine->SetPower(engine->GetPower() + 1);
	}	
}

