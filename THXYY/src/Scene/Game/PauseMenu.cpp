#include "PauseMenu.h"
#include "../../STGCore/STGCore.h"

static const int FADE_TIME = 30;

PauseMenu::PauseMenu() : Menu(32, 16, 384, 448)
{
	PauseMenuItem::texPauseMenu = AssetManager::GetInstance()->CreateTextureFromFile("res/menu/pause_menu.png");
}

PauseMenu::~PauseMenu()
{
	AssetManager::GetInstance()->DestroyTexture(PauseMenuItem::texPauseMenu);
}

void PauseMenu::DoPause()
{
	auto global = Global::GetInstance();
	black = new Sprite();
	black->SetTexture(global->texBlack);
	black->SetPosition(Vector3f(192, 224, 10));
	black->SetAlpha(0);
	black->AddTween(new FadeTo(0.75f, FADE_TIME, Tweener::EASE_OUT));
	AddChild(black);

	title = new PauseMenuItem(PauseMenuItem::PAUSE);
	title->SetPosition(Vector3f(-140, 440, 5));
	title->SetAlpha(0);
	title->AddTween(new MoveBy(Vector3f(140, -260, 5), FADE_TIME, Tweener::EASE_OUT));
	title->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::EASE_OUT));
	AddChild(title);

	AddMenuItem(new PauseMenuItem(PauseMenuItem::RESUME));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::RETURN_TO_TITLE));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::SAVE_REPLAY));
	AddMenuItem(new PauseMenuItem(PauseMenuItem::RETRY));

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);
		menuItem->SetPosition(Vector3f(-140, 440, 5));
		menuItem->SetAlpha(0);
		menuItem->AddTween(new MoveBy(Vector3f(150, -310 - 32 * i,0),FADE_TIME, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::EASE_OUT));
	}

	EventSystem::GetInstance()->RegisterKeyDownListener(this);
}

void PauseMenu::DoResume()
{
	black->AddTween(new FadeOut(FADE_TIME, Tweener::EASE_OUT));

	title->AddTween(new MoveTo(Vector3f(-140, 440, 5), FADE_TIME, Tweener::EASE_OUT));
	title->AddTween(new FadeOut(FADE_TIME, Tweener::EASE_OUT));

	for (int i = 0; i < GetItemCount(); i++)
	{
		auto menuItem = GetMenuItem(i);

		menuItem->AddTween(new MoveTo(Vector3f(-140, 440, 5), FADE_TIME, Tweener::EASE_OUT));
		menuItem->AddTween(new FadeOut(FADE_TIME, Tweener::EASE_OUT));
	}

	ClearItems();

	EventSystem::GetInstance()->UnRegisterKeyDownListener(this);
}

void PauseMenu::OnKeyDown(EngineObject* sender, int key)
{
	Menu::OnKeyDown(sender, key);
}