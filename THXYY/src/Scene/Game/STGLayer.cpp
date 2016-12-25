#include "STGLayer.h"
#include "../../STGCore/STGCore.h"

STGLayer::STGLayer() : Layer(32, 16, 384, 448)
{

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

void STGLayer::OnDestroy()
{
	Layer::OnDestroy();
}