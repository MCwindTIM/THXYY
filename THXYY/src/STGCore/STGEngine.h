#ifndef STGENGINE_H
#define STGENGINE_H

#include <THEngine.h>
#include "Player.h"
#include "Stage.h"
#include "../Scene/Game/GameScene.h"
#include "STGResources.h"
#include "Enemy\Enemy.h"
#include "Bullet\Bullet.h"

using namespace THEngine;

class STGEngine : public Object
{
public:
	enum Difficulty
	{
		EASY,
		NORMAL,
		HARD,
		LUNATIC,
		EXTRA
	};

	enum StageEnum
	{
		STAGE_01,
		STAGE_02,
		STAGE_03,
		STAGE_04,
		STAGE_05,
		STAGE_06,
		STAGE_EX
	};

private:
	static STGEngine* instance;
	Difficulty difficulty;
	long long score;
	long long hiScore;
	int life;
	int bomb;
	int power;
	int maxPower;
	int maxPoint;
	int graze;

	LinkedList<Enemy*> enemyList;
	LinkedList<Bullet*> bulletList;

	STGResources* stgResources;

	Player* player;

	GameScene* gameScene;

	Stage* stage;

	StageEnum stageEnum;

private:
	STGEngine();

public:
	virtual ~STGEngine();
	static STGEngine* GetInstance();
	static STGEngine* Create();

	inline void SetDifficulty(Difficulty diff) { this->difficulty = diff; }
	inline Difficulty GetDifficulty() { return difficulty; }

	inline void SetScore(long long score) { this->score = score; }
	inline long long GetScore() { return score; }
	
	inline void SetHiScore(long long hiScore) { this->hiScore = hiScore; }
	inline long long GetHiScore() { return hiScore; }

	inline void SetLife(int life) { this->life = life; }
	inline int GetLife() { return life; }

	inline void SetBomb(int bomb) { this->bomb = bomb; }
	inline int GetBomb() { return bomb; }

	inline void SetPower(int power) { this->power = power; }
	inline int GetPower() { return power; }

	inline void SetMaxPower(int power) { this->maxPower = power; }
	inline int GetMaxPower() { return maxPower; }

	inline void SetMaxPoint(int point) { this->maxPoint = point; }
	inline int GetMaxPoint() { return maxPoint; }

	inline void SetGraze(int graze) { this->graze = graze; }
	inline int GetGraze() { return graze; }

	inline void SetPlayer(Player* player)
	{
		TH_SAFE_RELEASE(this->player);
		this->player = player;
		this->player->Retain();
	}
	inline Player* GetPlayer() { return player; }

	inline void SetGameScene(GameScene* scene)
	{ 
		this->gameScene = scene;
	}
	inline GameScene* GetGameScene() { return gameScene; }

	inline void SetStageEnum(StageEnum stageEnum) { this->stageEnum = stageEnum; }
	inline StageEnum GetStageEnum() { return stageEnum; }

	void AddEnemy(Enemy* enemy);
	void AddBullet(Bullet* bullet);
	inline void AddObject(Sprite* object)
	{
		gameScene->GetSTGLayer()->AddChild(object);
	}

	inline void ShootBullet(Bullet* bullet)
	{
		ShootBullet(bullet, true, 1);
	}

	inline void ShootBullet(Bullet* bullet, bool hasFog)
	{
		ShootBullet(bullet, hasFog, 1);
	}

	void ShootBullet(Bullet* bullet, bool hasFog, int sound);

	void Update();

	void Init();

	void Shutdown();

	void LoadStage(Stage* stage);

	void OnLoad();

	void GameOver();

	friend class API;
};

#endif