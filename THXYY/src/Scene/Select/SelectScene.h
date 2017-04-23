#ifndef SELECT_SCENE_H
#define SELECT_SCENE_H

#include <THEngine.h>

using namespace THEngine;

class SelectTitle;
class RankSelectMenu;

class SelectScene : public Scene
{
private:
	Texture* texBackground = nullptr;
	Texture* texLoading = nullptr;

	Layer* bgrLayer = nullptr;
	RankSelectMenu* rankSelectMenu = nullptr;

	SelectTitle* title = nullptr;

	int frame = 0;

public:
	SelectScene();
	virtual ~SelectScene();

	virtual void Update() override;
	virtual void OnStart() override;

	void ShowRank();
	void Back();
	void StartGame();
};

#endif