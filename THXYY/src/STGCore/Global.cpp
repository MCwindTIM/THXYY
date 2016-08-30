#include "Global.h"

Global* Global::instance = nullptr;

Global::Global()
{
	
}

Global::~Global()
{

}

Global* Global::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Global();
	}
	return instance;
}

bool Global::LoadTextures()
{
	auto manager = AssetManager::GetInstance();
	texBlack = manager->CreateTextureFromFile("res/front/black.jpg");
	if (texBlack == nullptr)
	{
		return false;
	}
	return true;
}


