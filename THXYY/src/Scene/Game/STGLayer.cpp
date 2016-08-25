#include "STGLayer.h"
#include "../../STGCore/STGCore.h"

STGLayer::STGLayer() : Layer(32, 16, 384, 448)
{
	auto engine = STGEngine::GetInstance();

	auto player = engine->GetPlayer();

	AddChild(player);
}

STGLayer::~STGLayer()
{

}

void STGLayer::Update()
{
	Layer::Update();

	auto engine = STGEngine::GetInstance();
	engine->Update();
}