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

	THLog("加载STG纹理。。。");

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

	texBullet01 = manager->CreateTextureFromFile("res/bullet/bullet1.png");
	if (texBullet01 == nullptr)
	{
		return false;
	}

	texBullet02 = manager->CreateTextureFromFile("res/bullet/bullet2.png");
	if (texBullet02 == nullptr)
	{
		return false;
	}

	texBullet03 = manager->CreateTextureFromFile("res/bullet/bullet3.png");
	if (texBullet03 == nullptr)
	{
		return false;
	}

	texBullet04 = manager->CreateTextureFromFile("res/bullet/bullet4.png");
	if (texBullet04 == nullptr)
	{
		return false;
	}

	texReimu = manager->CreateTextureFromFile("res/player/reimu.png");
	if (texReimu == nullptr)
	{
		return false;
	}

	texEffBase = manager->CreateTextureFromFile("res/effect/eff_base.png");
	if (texEffBase == nullptr)
	{
		return false;
	}

	texPointLight = manager->CreateTextureFromFile("res/effect/point_light.png");
	if (texPointLight == nullptr)
	{
		return false;
	}

	texFourAngleStar = manager->CreateTextureFromFile("res/effect/four_angle_star.png");
	if (texFourAngleStar == nullptr)
	{
		return false;
	}

	THLog("加载STG纹理成功。");

	return true;
}

void STGResources::UnloadTextures()
{
	auto manager = AssetManager::GetInstance();

	THLog("释放STG纹理。");

	manager->DestroyTexture(texPlayerCenter);
	manager->DestroyTexture(texEnemy01);
	manager->DestroyTexture(texBullet01);
	manager->DestroyTexture(texBullet02);
	manager->DestroyTexture(texBullet03);
	manager->DestroyTexture(texBullet04);
	manager->DestroyTexture(texReimu);
	manager->DestroyTexture(texEffBase);
	manager->DestroyTexture(texPointLight);
	manager->DestroyTexture(texFourAngleStar);

	texPlayerCenter = nullptr;
	texEnemy01 = nullptr;
	texBullet01 = nullptr;
	texBullet02 = nullptr;
	texBullet03 = nullptr;
	texBullet04 = nullptr;
	texReimu = nullptr;
	texEffBase = nullptr;
	texPointLight = nullptr;
	texFourAngleStar = nullptr;
}

bool STGResources::LoadSounds()
{
	auto audio = Audio::GetInstance();

	soundShoot1 = audio->CreateSound("sound/se_tan00.wav");
	if (soundShoot1 == nullptr)
	{
		return false;
	}

	soundShoot2 = audio->CreateSound("sound/se_tan01.wav");
	if (soundShoot2 == nullptr)
	{
		return false;
	}

	soundShoot3 = audio->CreateSound("sound/se_tan02.wav");
	if (soundShoot3 == nullptr)
	{
		return false;
	}

	soundBiu = audio->CreateSound("sound/se_pldead00.wav");
	if (soundBiu == nullptr)
	{
		return false;
	}

	soundMenuOK = audio->CreateSound("sound/se_ok00.wav");
	if (soundMenuOK == nullptr)
	{
		return false;
	}

	soundMenuSelect = audio->CreateSound("sound/se_select00.wav");
	if (soundMenuSelect == nullptr)
	{
		return false;
	}

	soundItem = audio->CreateSound("sound/se_item00.wav");
	if (soundItem == nullptr)
	{
		return false;
	}

	soundDamage00 = audio->CreateSound("sound/se_damage00.wav");
	if (soundDamage00 == nullptr)
	{
		return false;
	}

	soundDamage01 = audio->CreateSound("sound/se_damage01.wav");
	if (soundDamage01 == nullptr)
	{
		return false;
	}

	soundEnemyDie00 = audio->CreateSound("sound/se_enep00.wav");
	if (soundEnemyDie00 == nullptr)
	{
		return false;
	}

	soundEnemyDie01 = audio->CreateSound("sound/se_enep01.wav");
	if (soundEnemyDie01 == nullptr)
	{
		return false;
	}

	soundPlayerShoot = audio->CreateSound("sound/se_plst00.wav");
	if (soundPlayerShoot == nullptr)
	{
		return false;
	}

	soundBomb = audio->CreateSound("sound/se_nep00.wav");
	if (soundBomb == nullptr)
	{
		return false;
	}

	soundExplode = audio->CreateSound("sound/se_cat00.wav");
	if (soundExplode == nullptr)
	{
		return false;
	}

	return true;
}

void STGResources::UnloadSounds()
{
	auto audio = Audio::GetInstance();

	audio->DestroySound(soundShoot1);
	audio->DestroySound(soundShoot2);
	audio->DestroySound(soundShoot3);
	audio->DestroySound(soundBiu);
	audio->DestroySound(soundMenuOK);
	audio->DestroySound(soundMenuSelect);
	audio->DestroySound(soundItem);
	audio->DestroySound(soundDamage00);
	audio->DestroySound(soundDamage01);
	audio->DestroySound(soundEnemyDie00);
	audio->DestroySound(soundEnemyDie01);
	audio->DestroySound(soundPlayerShoot);
	audio->DestroySound(soundBomb);
	audio->DestroySound(soundExplode);

	soundShoot1 = nullptr;
	soundShoot2 = nullptr;
	soundShoot3 = nullptr;
	soundBiu = nullptr;
	soundMenuOK = nullptr;
	soundMenuSelect = nullptr;
	soundItem = nullptr;
	soundDamage00 = nullptr;
	soundDamage01 = nullptr;
	soundEnemyDie00 = nullptr;
	soundEnemyDie01 = nullptr;
	soundPlayerShoot = nullptr;
	soundBomb = nullptr;
	soundExplode = nullptr;
}

