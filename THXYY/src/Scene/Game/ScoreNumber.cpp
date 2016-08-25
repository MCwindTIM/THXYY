#include "ScoreNumber.h"

void ScoreNumber::Update()
{
	Sprite::Update();
	switch (number)
	{
	case 0:
		SetTexRect(Rect(96, 109, 8, 24));
		break;
	case 1:
		SetTexRect(Rect(109, 122, 8, 24));
		break;
	case 2:
		SetTexRect(Rect(122, 135, 8, 24));
		break;
	case 3:
		SetTexRect(Rect(135, 148, 8, 24));
		break;
	case 4:
		SetTexRect(Rect(148, 161, 8, 24));
		break;
	case 5:
		SetTexRect(Rect(161, 174, 8, 24));
		break;
	case 6:
		SetTexRect(Rect(174, 187, 8, 24));
		break;
	case 7:
		SetTexRect(Rect(187, 200, 8, 24));
		break;
	case 8:
		SetTexRect(Rect(200, 213, 8, 24));
		break;
	case 9:
		SetTexRect(Rect(213, 226, 8, 24));
		break;
	default:
		break;
	}
}