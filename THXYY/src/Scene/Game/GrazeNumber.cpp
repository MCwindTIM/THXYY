#include "GrazeNumber.h"

void GrazeNumber::Update()
{
	Sprite::Update();
	switch (number)
	{
	case 0:
		SetTexRect(Rect(96, 109, 104, 120));
		break;
	case 1:
		SetTexRect(Rect(109, 122, 104, 120));
		break;
	case 2:
		SetTexRect(Rect(122, 135, 104, 120));
		break;
	case 3:
		SetTexRect(Rect(135, 148, 104, 120));
		break;
	case 4:
		SetTexRect(Rect(148, 161, 104, 120));
		break;
	case 5:
		SetTexRect(Rect(161, 174, 104, 120));
		break;
	case 6:
		SetTexRect(Rect(174, 187, 104, 120));
		break;
	case 7:
		SetTexRect(Rect(187, 200, 104, 120));
		break;
	case 8:
		SetTexRect(Rect(200, 213, 104, 120));
		break;
	case 9:
		SetTexRect(Rect(213, 226, 104, 120));
		break;
	default:
		break;
	}
}