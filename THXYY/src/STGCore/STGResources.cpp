#include "STGResources.h"

STGResources* STGResources::instance = nullptr;

STGResources::STGResources()
{
	texPlayerCenter = nullptr;
	texEnemy01 = nullptr;
	texBullet01 = nullptr;
}

STGResources::~STGResources()
{
	UnloadTextures();
	UnloadSounds();
}

STGResources* STGResources::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new STGResources();
	}
	return instance;
}

bool STGResources::LoadTexTures()
{
	auto manager = AssetManager::GetInstance();

	texPlayerCenter = manager->CreateTextureFromFile("res/player/center.png");
	if (texPlayerCenter == nullptr)
	{
		return false;
	}

	texEnemy01 = manager->CreateTextureFromFile("res/enemy/enemy01.png");
	if (texEnemy01 == nullptr)
	{
		return false;
	}

	texBullet01 = manager->CreateTextureFromFile("res/bullet/etama.png");
	if (texBullet01 == nullptr)
	{
		return false;
	}
	return true;
}

void STGResources::UnloadTextures()
{
	auto manager = AssetManager::GetInstance();

	manager->DestroyTexture(texPlayerCenter);
	manager->DestroyTexture(texEnemy01);
	manager->DestroyTexture(texBullet01);

	texPlayerCenter = nullptr;
	texEnemy01 = nullptr;
	texBullet01 = nullptr;
}

bool STGResources::LoadSounds()
{
	auto audio = Audio::GetInstance();

	soundShoot1 = audio->CreateSound("sound/se_tan00.wav");
	if (soundShoot1 == nullptr)
	{
		return false;
	}

	soundBiu = audio->CreateSound("sound/se_pldead00.wav");
	if (soundBiu == nullptr)
	{
		return false;
	}

	return true;
}

void STGResources::UnloadSounds()
{
	auto audio = Audio::GetInstance();

	audio->DestroySound(soundShoot1);
	audio->DestroySound(soundBiu);

	soundShoot1 = nullptr;
	soundBiu = nullptr;
}

