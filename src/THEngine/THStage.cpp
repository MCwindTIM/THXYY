#include "stdafx.h"
#include "THStage.h"

THStage::THStage()
{
	frame = 0;
}

void THStage::CommonUpdate()
{
	frame++;
	Update();
}

void THStage::CommonDraw()
{
	Draw();
}