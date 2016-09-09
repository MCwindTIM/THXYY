#include "TitleMenuItem.h"

Texture* TitleMenuItem::texTitleMenu = nullptr;

TitleMenuItem::TitleMenuItem(Type type)
{
	SetTexture(texTitleMenu);

	switch (type)
	{
	case GAME_START:
		SetTexRect(Rect(128, 256, 0, 32));
		break;
	case EXTRA_START:
		SetTexRect(Rect(128, 256, 32, 64));
		break;
	case PRACTICE_START:
		SetTexRect(Rect(128, 256, 96, 128));
		break;
	case SPELL_PRACTICE:
		SetTexRect(Rect(128, 256, 128, 160));
		break;
	case REPLAY:
		SetTexRect(Rect(128, 256, 160, 192));
		break;
	case PLAYER_DATA:
		SetTexRect(Rect(128, 256, 192, 224));
		break;
	case MUSIC_ROOM:
		SetTexRect(Rect(128, 256, 224, 256));
		break;
	case OPTION:
		SetTexRect(Rect(128, 256, 256, 288));
		break;
	case MANUAL:
		SetTexRect(Rect(128, 256, 288, 320));
		break;
	case QUIT:
		SetTexRect(Rect(128, 256, 320, 352));
		break;
	}
}

TitleMenuItem::~TitleMenuItem()
{

}

void TitleMenuItem::OnSelect()
{
	MenuItem::OnSelect();

	texRect.left -= 128;
	texRect.right -= 128;
}

void TitleMenuItem::OnDeselect()
{
	MenuItem::OnDeselect();

	texRect.left += 128;
	texRect.right += 128;
}