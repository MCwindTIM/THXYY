#include "PowerNumber.h"

void PowerNumber::Update()
{
	Sprite::Update();

	switch (number)
	{
	case 0:
		SetTexRect(Rect(96, 109, 40, 56));
		break;
	case 1:
		SetTexRect(Rect(109, 122, 40, 56));
		break;
	case 2:
		SetTexRect(Rect(122, 135, 40, 56));
		break;
	case 3:
		SetTexRect(Rect(135, 148, 40, 56));
		break;
	case 4:
		SetTexRect(Rect(148, 161, 40, 56));
		break;
	case 5:
		SetTexRect(Rect(161, 174, 40, 56));
		break;
	case 6:
		SetTexRect(Rect(174, 187, 40, 56));
		break;
	case 7:
		SetTexRect(Rect(187, 200, 40, 56));
		break;
	case 8:
		SetTexRect(Rect(200, 213, 40, 56));
		break;
	case 9:
		SetTexRect(Rect(213, 226, 40, 56));
		break;
	default:
		break;
	}
}