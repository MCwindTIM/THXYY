#include "STGEngine.h"
#include "Global.h"
#include "Effect\BulletFog.h"
#include "../Player/Reimu.h"
#include "../Stage/Stage01.h"

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

	gameOver = false;
}

void STGEngine::Start()
{
	auto global = Global::GetInstance();

	SetLife(2);
	SetBomb(3);
	SetPower(100);
	SetMaxPower(400);
	SetMaxPoint(10000);
	SetScore(0);
	SetGraze(0);
	SetDifficulty(STGEngine::NORMAL);

	switch (global->playerEnum)
	{
	case Global::REIMU:
		player = new Reimu();
	}
	player->Retain();

	((GameScene*)Game::GetInstance()->GetScene())->GetSTGLayer()->AddChild(player);

	Stage* stage = nullptr;
	switch (global->stageEnum)
	{
	case Global::STAGE_01:
		stage = new Stage01();
	}

	LoadStage(stage);
}

void STGEngine::Clear()
{
	auto iter = enemyList.GetIterator();
	while (iter->HasNext())
	{
		iter->Next()->MarkDestroy();
	}

	auto iter2 = bulletList.GetIterator();
	while (iter2->HasNext())
	{
		iter2->Next()->MarkDestroy();
	}

	player->MarkDestroy();

	enemyList.Clear();
	bulletList.Clear();

	TH_SAFE_RELEASE(player);
	TH_SAFE_RELEASE(stage);
}

void STGEngine::Restart()
{
	Clear();
	Start();
}

void STGEngine::Shutdown()
{
	Clear();

	stgResources->UnloadTextures();
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
	Start();
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
	auto scene = (GameScene*)Game::GetInstance()->GetScene();
	scene->GetPauseMenu()->DoGameOver();
	scene->GetSTGLayer()->Pause();

	gameOver = true;
}