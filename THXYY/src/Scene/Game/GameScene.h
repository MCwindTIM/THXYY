#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <THEngine.h>
#include "ScoreNumber.h"
#include "PowerNumber.h"
#include "STGLayer.h"
#include "PauseMenu.h"

using namespace THEngine;

class GameScene : public Scene, public IKeyDownListener
{
private:
	const float SCORE_LEFT = 492.0f;
	const float POWER_LEFT = 530.0f;

	STGLayer* stgLayer;
	PauseMenu* pauseMenu = nullptr;

	Layer* baseLayer;
	Texture* texGameBg;
	Texture* texGameBg2;

	ScoreNumber* hiScore[10];
	ScoreNumber* score[10];

	Sprite* lifeSprite[8];
	Sprite* bombSprite[8];

	PowerNumber* powerSprite[6];

public:
	GameScene();
	virtual ~GameScene();

	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnLoad() override;
	virtual void OnSceneChanged() override;

	virtual void OnKeyDown(EngineObject* sender, int key) override;

	void UpdateScore();
	void UpdateLifeAndBomb();
	void UpdatePower();
	void DrawMaxPoint();
	void DrawGraze();
	void CreateScorePanel();
	void CreatePowerPanel();

	inline STGLayer* GetSTGLayer() { return stgLayer; }
};

#endif