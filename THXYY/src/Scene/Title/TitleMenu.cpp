#include "TitleMenu.h"
#include "../Game/GameScene.h"
#include "../../STGCore/STGEngine.h"
#include "../../Player/Reimu.h"
#include "../../Stage/Stage01.h"

using namespace THEngine;

TitleMenu::TitleMenu() : Layer(464, 216, 128, 248)
{
	currentItem = 0;
	itemCount = 10;

	texMenuItem = AssetManager::GetInstance()->CreateTextureFromFile("res/title/main_menu.png");

	for (int i = 0; i < 10; i++)
	{
		if (i < 2)
		{
			spriteRect[i][0] = Rect(0, 128, 32 * i, 32 * (i + 1));
			spriteRect[i][1] = Rect(128, 256, 32 * i, 32 * (i + 1));
		}
		else
		{
			spriteRect[i][0] = Rect(0, 128, 32 * (i + 1), 32 * (i + 2));
			spriteRect[i][1] = Rect(128, 256, 32 * (i + 1), 32 * (i + 2));
		}
	}

	spriteRect[1][2] = Rect(0, 128, 64, 96);

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

TitleMenu::~TitleMenu()
{
	AssetManager::GetInstance()->DestroyTexture(texMenuItem);
	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void TitleMenu::OnKeyDown(EngineObject* sender, int key)
{
	int oldItem = currentItem;
	if (key == VK_UP)
	{
		if (currentItem > 0)
		{
			currentItem--;
		}
	}
	else if (key == VK_DOWN)
	{
		if (currentItem < itemCount - 1)
		{
			currentItem++;
		}
	}
	else if (key == 'Z' || key == VK_RETURN)
	{
		switch (currentItem)
		{
		case 0:
		{
			auto engine = STGEngine::GetInstance();

			engine->Init();

			engine->SetLife(2);
			engine->SetBomb(3);
			engine->SetPower(100);
			engine->SetMaxPower(400);
			engine->SetMaxPoint(10000);
			engine->SetScore(0);
			engine->SetGraze(0);
			engine->SetDifficulty(STGEngine::NORMAL);

			Player* player = new Reimu();
			engine->SetPlayer(player);

			Global::stageEnum = Global::STAGE_01;

			GameScene* scene = new GameScene();
			Game::GetInstance()->LoadScene(scene);

			break;
		}		
		case 9:
			Game::GetInstance()->Quit();
		}
		
	}
	OnMenuItemChanged(oldItem, currentItem);
}

void TitleMenu::Update()
{
	Layer::Update();
}

void TitleMenu::Draw()
{
	Layer::Draw();
	Sprite* sprite = new Sprite();
	sprite->SetTexture(texMenuItem);
	for (int i = 0; i < itemCount; i++)
	{
		if (currentItem == i)
		{
			sprite->SetTexRect(spriteRect[i][0]);
		}
		else
		{
			sprite->SetTexRect(spriteRect[i][1]);
		}
		sprite->SetPosition(Vector3f(64, 232 - 24 * i, 0));
		sprite->Draw();
	}
	delete sprite;
}

void TitleMenu::DrawMenuItem(int item)
{

}

void TitleMenu::OnMenuItemSelected(int item)
{

}

void TitleMenu::OnMenuItemChanged(int previousItem, int currentItem)
{

}