#include "stdafx.h"
#include "../Engine_Core.h"
#include "THBiuEffect.h"

#define BIUEFFECT1_FRAME_INTERVAL                     3

THBiuEffect1::THBiuEffect1()
{
	Init();
}

void THBiuEffect1::Init()
{
	frame = 0;
	SetTexture(engine->_texEffect1);
}

void THBiuEffect1::Update()
{
	frame++;
	if(frame > 24){
		MarkDelete();
	}
}

void THBiuEffect1::Draw()
{
	ClearTransform();
	if (frame <= BIUEFFECT1_FRAME_INTERVAL){
		SetImgRect(0, 0, 128, 128);
	}
	else if (frame <= 2 * BIUEFFECT1_FRAME_INTERVAL){
		SetImgRect(128, 0, 256, 128);
	}
	else if (frame <= 3 * BIUEFFECT1_FRAME_INTERVAL){
		SetImgRect(256, 0, 384, 128);
	}
	else{
		SetImgRect(384, 0, 512, 128);
		SetScale(x, y, 1 + 0.05 * (frame - 3 * BIUEFFECT1_FRAME_INTERVAL), 1 + 0.05 * (frame - 3 * BIUEFFECT1_FRAME_INTERVAL));
	}

	float alpha = (24 - frame) *(1.0f / 24.0f);
	if (alpha >= 0){
		SetAlpha(alpha);
	}
	else{
		SetAlpha(0);
	}

	DrawImg(x, y, 2, DRAW_CENTERED);
}