#include "Player.h"
#include "STGEngine.h"
#include "Global.h"
#include "Effect\BulletFog.h"

using namespace THEngine;

STGEngine* STGEngine::instance = nullptr;

STGEngine::STGEngine()
{
	ASSERT(instance == nullptr);

	score = hiScore = 0;

	stgResources = STGResources::GetInstance();
	stgResources->Retain();

	player = nullptr;
	gameScene = nullptr;
	stage = nullptr;
}

STGEngine::~STGEngine()
{
	TH_SAFE_RELEASE(stgResources);
	TH_SAFE_RELEASE(player);
	TH_SAFE_RELEASE(stage);
}

STGEngine* STGEngine::GetInstance()
{
	return instance;
}

STGEngine* STGEngine::Create()
{
	if (instance)
	{
		return nullptr;
	}
	STGEngine* engine =  new STGEngine();
	engine->SetDifficulty(NORMAL);
	instance = engine;
	return engine;
}

void STGEngine::Init()
{
	stgResources->LoadTexTures();
}

void STGEngine::Shutdown()
{
	stgResources->UnloadTextures();

	enemyList.Clear();

	TH_SAFE_RELEASE(player);
	TH_SAFE_RELEASE(stage);
}

void STGEngine::Update()
{
	if (stage)
	{
		stage->Update();
	}
}

void STGEngine::LoadStage(Stage* stage)
{
	this->stage = stage;
	this->stage->Retain();
	this->stage->OnLoad();

	player->SetPosition(192.0f, 48.0f);
}

void STGEngine::OnLoad()
{

}

void STGEngine::AddEnemy(Enemy* enemy)
{
	enemyList.Add(enemy);
	gameScene->GetSTGLayer()->AddChild(enemy);
}

void STGEngine::AddBullet(Bullet* bullet)
{
	bulletList.Add(bullet);
	gameScene->GetSTGLayer()->AddChild(bullet);
}

void STGEngine::ShootBullet(Bullet* bullet, bool hasFog, int sound)
{
	auto stgResources = STGResources::GetInstance();

	if (hasFog)
	{
		BulletFog* fog = new BulletFog(bullet);
		AddObject(fog);
	}
	else
	{
		AddBullet(bullet);
	}

	if (sound)
	{
		switch (sound)
		{
		case 1:
			stgResources->soundShoot1->Play();
			break;
		default:
			break;
		}
	}
}

void STGEngine::GameOver()
{

}