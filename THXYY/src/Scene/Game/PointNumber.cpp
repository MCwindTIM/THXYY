#include "PointNumber.h"

void PointNumber::Update()
{
	Sprite::Update();
	switch (number)
	{
	case 0:
		SetTexRect(Rect(96, 109, 72, 88));
		break;
	case 1:
		SetTexRect(Rect(109, 122, 72, 88));
		break;
	case 2:
		SetTexRect(Rect(122, 135, 72, 88));
		break;
	case 3:
		SetTexRect(Rect(135, 148, 72, 88));
		break;
	case 4:
		SetTexRect(Rect(148, 161, 72, 88));
		break;
	case 5:
		SetTexRect(Rect(161, 174, 72, 88));
		break;
	case 6:
		SetTexRect(Rect(174, 187, 72, 88));
		break;
	case 7:
		SetTexRect(Rect(187, 200, 72, 88));
		break;
	case 8:
		SetTexRect(Rect(200, 213, 72, 88));
		break;
	case 9:
		SetTexRect(Rect(213, 226, 72, 88));
		break;
	default:
		break;
	}
}