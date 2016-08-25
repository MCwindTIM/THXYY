#include "GameScene.h"
#include "../../STGCore/STGCore.h"
#include "PointNumber.h"
#include "GrazeNumber.h"
#include "../../Stage/Stage01.h"

using namespace THEngine;

GameScene::GameScene()
{
	STGEngine* engine = STGEngine::GetInstance();
	engine->SetGameScene(this);

	AssetManager* manager = AssetManager::GetInstance();
	texGameBg = manager->CreateTextureFromFile("res/front/gamebg.jpg");
	texGameBg2 = manager->CreateTextureFromFile("res/front/gamebg2.png");

	baseLayer = new Layer();
	baseLayer->SetOrder(100);
	AddLayer(baseLayer);

	stgLayer = new STGLayer();
	stgLayer->SetOrder(10);
	AddLayer(stgLayer);

	Sprite* background = new Sprite();
	background->SetTexture(texGameBg);
	background->SetPivot(Vector2f(0.0f, 0.0f));
	background->SetPosition(Vector3f(0.0f, 0.0f, 100.0f));
	baseLayer->AddChild(background);

	//创建难度栏
	Sprite* difficulty = new Sprite();
	difficulty->SetTexture(texGameBg2);
	difficulty->SetPosition(Vector3f(528.0f, 448.0f, 1.0f));
	switch(engine->GetDifficulty())
	{
	case STGEngine::EASY:
		difficulty->SetTexRect(Rect(0.0f, 96.0f, 0.0f, 32.0f));
		break;
	case STGEngine::NORMAL:
		difficulty->SetTexRect(Rect(0.0f, 96.0f, 32.0f, 64.0f));
		break;
	case STGEngine::HARD:
		difficulty->SetTexRect(Rect(0.0f, 96.0f, 64.0f, 96.0f));
		break;
	case STGEngine::LUNATIC:
		difficulty->SetTexRect(Rect(0.0f, 96.0f, 96.0f, 128.0f));
		break;
	case STGEngine::EXTRA:
		difficulty->SetTexRect(Rect(0.0f, 96.0f, 128.0f, 160.0f));
		break;
	default:
		break;
	}
	baseLayer->AddChild(difficulty);

	//创建分数栏
	CreateScorePanel();

	//创建残机和符卡栏
	for (int i = 0; i < 8; i++)
	{
		lifeSprite[i] = new Sprite();
		lifeSprite[i]->SetTexture(texGameBg2);
		lifeSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		lifeSprite[i]->SetPosition(Vector3f(SCORE_LEFT - 5 + 18 * i, 340.0f, 1.0f));
		baseLayer->AddChild(lifeSprite[i]);

		bombSprite[i] = new Sprite();
		bombSprite[i]->SetTexture(texGameBg2);
		bombSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		bombSprite[i]->SetPosition(Vector3f(SCORE_LEFT - 5 + 18 * i, 314.0f, 1.0f));
		baseLayer->AddChild(bombSprite[i]);
	}

	//创建灵力栏
	CreatePowerPanel();
}

GameScene::~GameScene()
{
	AssetManager* manager = AssetManager::GetInstance();
	manager->DestroyTexture(texGameBg);
	manager->DestroyTexture(texGameBg2);
}

void GameScene::Update()
{
	Scene::Update();

	UpdateScore();
	UpdateLifeAndBomb();
	UpdatePower();
}

void GameScene::Draw()
{
	Scene::Draw();
	Application::GetInstance()->SetOrtho(0, 0, Game::GetInstance()->GetWidth(), Game::GetInstance()->GetHeight(), 0, 100);
	Application::GetInstance()->SetViewport(0, 0, Game::GetInstance()->GetWidth(), Game::GetInstance()->GetHeight());
	DrawMaxPoint();
	DrawGraze();
}

void GameScene::OnLoad()
{
	Scene::OnLoad();

	auto engine = STGEngine::GetInstance();

	engine->OnLoad();

	Stage01* stage = new Stage01();
	engine->LoadStage(stage);
}

void GameScene::OnSceneChanged()
{
	Scene::OnSceneChanged();

	auto engine = STGEngine::GetInstance();
	engine->SetGameScene(nullptr);
}

void GameScene::CreateScorePanel()
{
	for (int i = 0; i < 10; i++)
	{
		hiScore[i] = new ScoreNumber();
		hiScore[i]->SetTexture(texGameBg2);
		hiScore[i]->SetPivot(Vector2f(0.0f, 0.0f));
		baseLayer->AddChild(hiScore[i]);

		score[i] = new ScoreNumber();
		score[i]->SetTexture(texGameBg2);
		score[i]->SetPosition(Vector3f(SCORE_LEFT + 13 * i, 382.0f, 1.0f));
		score[i]->SetPivot(Vector2f(0.0f, 0.0f));
		baseLayer->AddChild(score[i]);
	}

	hiScore[0]->SetPosition(Vector3f(SCORE_LEFT, 410.0f, 1.0f));
	for (int j = 1; j < 4; j++)
	{
		hiScore[j]->SetPosition(Vector3f(SCORE_LEFT + 18 + 13 * (j - 1), 410.0f, 1.0f));
	}
	for (int j = 4; j < 7; j++)
	{
		hiScore[j]->SetPosition(Vector3f(SCORE_LEFT + 62 + 13 * (j - 4), 410.0f, 1.0f));
	}
	for (int j = 7; j < 10; j++)
	{
		hiScore[j]->SetPosition(Vector3f(SCORE_LEFT + 106 + 13 * (j - 7), 410.0f, 1.0f));
	}

	score[0]->SetPosition(Vector3f(SCORE_LEFT, 382.0f, 1.0f));
	for (int j = 1; j < 4; j++)
	{
		score[j]->SetPosition(Vector3f(SCORE_LEFT + 18 + 13 * (j - 1), 382.0f, 1.0f));
	}
	for (int j = 4; j < 7; j++)
	{
		score[j]->SetPosition(Vector3f(SCORE_LEFT + 62 + 13 * (j - 4), 382.0f, 1.0f));
	}
	for (int j = 7; j < 10; j++)
	{
		score[j]->SetPosition(Vector3f(SCORE_LEFT + 106 + 13 * (j - 7), 382.0f, 1.0f));
	}

	Sprite* comma[6];
	for (int i = 0; i < 6; i++)
	{
		comma[i] = new Sprite();
		comma[i]->SetTexture(texGameBg2);
		comma[i]->SetPivot(Vector2f(0.0f, 0.0f));
		comma[i]->SetTexRect(Rect(226, 231, 8, 24));
		baseLayer->AddChild(comma[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		comma[i]->SetPosition(Vector3f(SCORE_LEFT + 13 + 44 * i, 410.0f, 1.0f));
	}
	for (int i = 3; i < 6; i++)
	{
		comma[i]->SetPosition(Vector3f(SCORE_LEFT + 13 + 44 * (i - 3), 382.0f, 1.0f));
	}
}

void GameScene::CreatePowerPanel()
{
	powerSprite[0] = new PowerNumber();
	powerSprite[0]->SetTexture(texGameBg2);
	powerSprite[0]->SetPivot(Vector2f(0.0f, 0.0f));
	powerSprite[0]->SetPosition(Vector3f(POWER_LEFT, 276.0f, 1.0f));
	baseLayer->AddChild(powerSprite[0]);

	Sprite* point1 = new Sprite();
	point1->SetTexture(texGameBg2);
	point1->SetTexRect(Rect(242.0f, 248.0f, 40.0f, 56.0f));
	point1->SetPivot(Vector2f(0.0f, 0.0f));
	point1->SetPosition(Vector3f(POWER_LEFT + 13, 276.0f, 1.0f));
	baseLayer->AddChild(point1);

	for (int i = 1; i < 3; i++)
	{
		powerSprite[i] = new PowerNumber();
		powerSprite[i]->SetTexture(texGameBg2);
		powerSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		powerSprite[i]->SetPosition(Vector3f(POWER_LEFT + 13 * i + 6, 276.0f, 1.0f));
		baseLayer->AddChild(powerSprite[i]);
	}

	Sprite* gang = new Sprite();
	gang->SetTexture(texGameBg2);
	gang->SetTexRect(Rect(232.0f, 242.0f, 40.0f, 56.0f));
	gang->SetPivot(Vector2f(0.0f, 0.0f));
	gang->SetPosition(Vector3f(POWER_LEFT + 45, 276.0f, 1.0f));
	baseLayer->AddChild(gang);

	powerSprite[3] = new PowerNumber();
	powerSprite[3]->SetTexture(texGameBg2);
	powerSprite[3]->SetPivot(Vector2f(0.0f, 0.0f));
	powerSprite[3]->SetPosition(Vector3f(POWER_LEFT + 55, 276.0f, 1.0f));
	baseLayer->AddChild(powerSprite[3]);

	Sprite* point2 = new Sprite();
	point2->SetTexture(texGameBg2);
	point2->SetTexRect(Rect(242.0f, 248.0f, 40.0f, 56.0f));
	point2->SetPivot(Vector2f(0.0f, 0.0f));
	point2->SetPosition(Vector3f(POWER_LEFT + 68, 276.0f, 1.0f));
	baseLayer->AddChild(point2);

	for (int i = 4; i < 6; i++)
	{
		powerSprite[i] = new PowerNumber();
		powerSprite[i]->SetTexture(texGameBg2);
		powerSprite[i]->SetPivot(Vector2f(0.0f, 0.0f));
		powerSprite[i]->SetPosition(Vector3f(POWER_LEFT + 13 * i + 22, 276.0f, 1.0f));
		baseLayer->AddChild(powerSprite[i]);
	}
}

void GameScene::UpdateScore()
{
	STGEngine* engine = STGEngine::GetInstance();

	long long temp1 = engine->GetScore(), temp2 = engine->GetHiScore(); 
	for (int i = 0; i < 10; i++)
	{
		score[9 - i]->SetNumber(temp1 % 10);
		temp1 /= 10;
		hiScore[9 - 1]->SetNumber(temp2 % 10);
		temp2 /= 10;
	}
}

void GameScene::UpdateLifeAndBomb()
{
	STGEngine* engine = STGEngine::GetInstance();
	int life = engine->GetLife();
	int bomb = engine->GetBomb();

	int lifeInt = (int)life;
	lifeInt = lifeInt < 0 ? 0 : lifeInt;
	for (int i = 0; i < lifeInt; i++)
	{
		lifeSprite[i]->SetTexRect(Rect(7.0f, 25.0f, 180.0f, 204.0f));
	}
	for (int i = lifeInt; i < 8; i++)
	{
		lifeSprite[i]->SetTexRect(Rect(39.0f, 57.0f, 180.0f, 204.0f));
	}

	int bombInt = (int)bomb;
	bombInt = bombInt < 0 ? 0 : bombInt;
	for (int i = 0; i < bombInt; i++)
	{
		bombSprite[i]->SetTexRect(Rect(7.0f, 25.0f, 212.0f, 236.0f));
	}
	for (int i = bombInt; i < 8; i++)
	{
		bombSprite[i]->SetTexRect(Rect(39.0f, 57.0f, 212.0f, 236.0f));
	}
}

void GameScene::UpdatePower()
{
	STGEngine* engine = STGEngine::GetInstance();
	int power = engine->GetPower();
	int maxPower = engine->GetMaxPower();
	int temp1 = power;
	int temp2 = maxPower;

	for (int i = 0; i < 3; i++)
	{
		powerSprite[2 - i]->SetNumber(temp1 % 10);
		temp1 /= 10;
		powerSprite[5 - i]->SetNumber(temp2 % 10);
		temp2 /= 10;
	}
}

void GameScene::DrawMaxPoint()
{
	STGEngine* engine = STGEngine::GetInstance();
	int maxPoint = engine->GetMaxPoint();

	PointNumber* pointSprite = new PointNumber();
	pointSprite->SetTexture(texGameBg2);
	pointSprite->SetPivot(Vector2f(0.0f, 0.0f));

	int temp = maxPoint;
	for (int i = 0; temp > 0; i++)
	{
		pointSprite->SetNumber(temp % 10);
		pointSprite->SetPosition(Vector3f(POWER_LEFT + 87.0f - 13.0f * i, 252.0f, 1.0f));
		pointSprite->Update();
		pointSprite->Draw();
		temp /= 10;
	}
	delete pointSprite;
}

void GameScene::DrawGraze()
{
	STGEngine* engine = STGEngine::GetInstance();
	int graze = engine->GetGraze();

	GrazeNumber* grazeSprite = new GrazeNumber();
	grazeSprite->SetTexture(texGameBg2);
	grazeSprite->SetPivot(Vector2f(0.0f, 0.0f));

	int temp = graze;
	if (temp == 0)
	{
		grazeSprite->SetNumber(0);
		grazeSprite->SetPosition(Vector3f(POWER_LEFT + 87.0f, 228.0f, 1.0f));
		grazeSprite->Update();
		grazeSprite->Draw();
	}
	else for (int i = 0; temp > 0; i++)
	{
		grazeSprite->SetNumber(temp % 10);
		grazeSprite->SetPosition(Vector3f(POWER_LEFT + 87.0f - 13.0f * i, 228.0f, 1.0f));
		grazeSprite->Update();
		grazeSprite->Draw();
		temp /= 10;
	}
	delete grazeSprite;
}

