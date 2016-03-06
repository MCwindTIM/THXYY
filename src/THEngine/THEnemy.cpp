#include "stdafx.h"
#include "THEnemy.h"
#include "THCommon.h"
#include "THEngine.h"
#include "Effect/THFog.h"
#include "Effect/THMaple.h"

THEnemy::THEnemy()
{
	EnableAutoDelete();
	frame = 0;
	frame_for_anm = 0;
}

void THEnemy::Create(UINT id)
{

}

void THEnemy::CommonUpdate()
{
	if (delay > 0){
		delay--;
		return;
	}
	frame++;
	frame_for_anm++;
	if (life <= 0){
		MarkDelete();
		CommonDestroy();
		engine->_score += this->score;
	}
	Update();
}

void THEnemy::CommonDestroy(){
	Destroy();
}

void THEnemy::Update()
{
	UpdatePosition();
}

void THEnemy::Draw()
{

}

void THEnemy::CommonDraw()
{
	if (delay > 0){
		return;
	}
	Draw();
}

bool THEnemy::Hit(int x, int y, float radius)
{
	return false;
}

Fairy::Fairy()
{
	SetTexture(engine->_texEnemy);
	SetDamageRect(24, 24);
	SetRange(-16, 400, -16, 464);
	prev_direction = NONE;
}

Fairy::Fairy(BYTE type){
	SetTexture(engine->_texEnemy);
	SetDamageRect(24, 24);
	frame_for_anm = 0;
	SetRange(-16, 400, -16, 464);
	prev_direction = NONE;
	this->type = type;
}

void Fairy::Draw(){
	ClearTransform();
	int left, top, width, height;
	width = height = 32;
	switch (this->type){
	case FAIRY_BLUE1:
		top = 0;
		break;
	case FAIRY_BLUE2:
		top = 256;
		break;
	case FAIRY_RED1:
		top = 32;
		break;
	case FAIRY_RED2:
		top = 288;
		break;
	case FAIRY_GREEN1:
		top = 64;
		break;
	case FAIRY_GREEN2:
		top = 320;
		break;
	case FAIRY_YELLOW1:
		top = 96;
		break;
	case FAIRY_YELLOW2:
		top = 352;
		break;
	}

	if (ZERO(vx)){
		if (prev_direction == RIGHT){
			frame_for_anm = 1 + 6 * FRAME_INTERVAL;
			left = 224 - ((frame_for_anm - 1 - 6 * FRAME_INTERVAL) / FRAME_INTERVAL) * 32;
		}
		else if (prev_direction == LEFT){
			frame_for_anm = 1 + 6 * FRAME_INTERVAL;
			left = 224 - ((frame_for_anm - 1 - 6 * FRAME_INTERVAL) / FRAME_INTERVAL) * 32;
			SetReversalX(x);
		}
		else{
			if (frame_for_anm == 1 + 4 * FRAME_INTERVAL || frame_for_anm == 1 + 10 * FRAME_INTERVAL){
				frame_for_anm = 1;
			}
			if (frame_for_anm <= 4 * FRAME_INTERVAL){
				left = 32 * ((frame_for_anm - 1) / FRAME_INTERVAL);
			}
			else{
				left = 224 - ((frame_for_anm - 1 - 6 * FRAME_INTERVAL) / FRAME_INTERVAL) * 32;
			}
		}
		prev_direction = VERT;
	}
	else {
		if (prev_direction == VERT){
			frame_for_anm = 1;
		}
		else{
			if (frame_for_anm > 8 * FRAME_INTERVAL || frame_for_anm == 1){
				frame_for_anm = 1 + 4 * FRAME_INTERVAL;
			}
		}
		left = 128 + ((frame_for_anm - 1) / FRAME_INTERVAL) * 32;
		if (vx > 0){
			prev_direction = RIGHT;
		}
		else{
			prev_direction = LEFT;
			SetReversalX(x);
		}
	}

	SetImgRect(left, top, left + width, top + height);
	DrawImg(x, y, 64, DRAW_CENTERED);
}

void Fairy::CommonDestroy(){
	THFog *fog1 = NULL, *fog2 = NULL;
	THMaple *maples[8];
	switch (type){
	case FAIRY_RED1:
	case FAIRY_RED2:
		fog1 = new THEnemyFog(ENEMY_FOG_RED1);
		fog2 = new THEnemyFog(ENEMY_FOG_RED2);
		for (int i = 0; i < 8; i++){
			int random = Random(0, 1);
			if (random == 0){
				maples[i] = new THMaple(MAPLE_RED, ROTATION_CLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
			else{
				maples[i] = new THMaple(MAPLE_RED, ROTATION_ANTICLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
		}
		break;
	case FAIRY_GREEN1:
	case FAIRY_GREEN2:
		fog1 = new THEnemyFog(ENEMY_FOG_GREEN1);
		fog2 = new THEnemyFog(ENEMY_FOG_GREEN2);
		for (int i = 0; i < 8; i++){
			int random = Random(0, 1);
			if (random == 0){
				maples[i] = new THMaple(MAPLE_GREEN, ROTATION_CLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
			else{
				maples[i] = new THMaple(MAPLE_GREEN, ROTATION_ANTICLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
		}
		break;
	case FAIRY_BLUE1:
	case FAIRY_BLUE2:
		fog1 = new THEnemyFog(ENEMY_FOG_BLUE1);
		fog2 = new THEnemyFog(ENEMY_FOG_BLUE2);
		for (int i = 0; i < 8; i++){
			int random = Random(0, 1);
			if (random == 0){
				maples[i] = new THMaple(MAPLE_BLUE, ROTATION_CLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
			else{
				maples[i] = new THMaple(MAPLE_BLUE, ROTATION_ANTICLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
		}
		break;
	case FAIRY_YELLOW1:
	case FAIRY_YELLOW2:
		fog1 = new THEnemyFog(ENEMY_FOG_YELLOW1);
		fog2 = new THEnemyFog(ENEMY_FOG_YELLOW2);
		for (int i = 0; i < 8; i++){
			int random = Random(0, 1);
			if (random == 0){
				maples[i] = new THMaple(MAPLE_YELLOW, ROTATION_CLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
			else{
				maples[i] = new THMaple(MAPLE_YELLOW, ROTATION_ANTICLOCKWISE, 60, Random(1, 10), Random(0, 360));
			}
		}
		break;
	}
	fog1->SetPosition(x, y);
	fog2->SetPosition(x, y);
	AddRenderObject(fog1);
	AddRenderObject(fog2);
	for (int i = 0; i < 8; i++){
		maples[i]->SetPosition(x, y);
		maples[i]->SetVelocity(Random(1, 3));
		maples[i]->SetAngle(Random(0, 360));
		AddRenderObject(maples[i]);
	}
	Destroy();
}

ButterFly::ButterFly(){
	SetTexture(engine->_texEnemy);
	SetDamageRect(48, 48);
	SetRange(-32, 416, -32, 480);
	prev_direction = NONE;
}

void ButterFly::Draw(){
	ClearTransform();
	int left, top, width, height;
	width = height = 64;
	if (ZERO(vx)){
		top = 384;
		if (prev_direction == RIGHT){
			frame_for_anm = 1 + 6 * FRAME_INTERVAL;
			left = 448 - ((frame_for_anm - 1 - 6 * FRAME_INTERVAL) / FRAME_INTERVAL) * 64;
		}
		else if (prev_direction == LEFT){
			frame_for_anm = 1 + 6 * FRAME_INTERVAL;
			left = 448 - ((frame_for_anm - 1 - 6 * FRAME_INTERVAL) / FRAME_INTERVAL) * 64;
			SetReversalX(x);
		}
		else{
			if (frame_for_anm == 1 + 4 * FRAME_INTERVAL || frame_for_anm == 1 + 10 * FRAME_INTERVAL){
				frame_for_anm = 1;
			}
			if (frame_for_anm <= 4 * FRAME_INTERVAL){
				left = 64 * ((frame_for_anm - 1) / FRAME_INTERVAL);
			}
			else{
				left = 448 - ((frame_for_anm - 1 - 6 * FRAME_INTERVAL) / FRAME_INTERVAL) * 64;
			}
		}
		prev_direction = VERT;
	}
	else {
		if (prev_direction == VERT){
			frame_for_anm = 1;
		}
		else{
			if (frame_for_anm > 8 * FRAME_INTERVAL || frame_for_anm == 1){
				frame_for_anm = 1 + 4 * FRAME_INTERVAL;
			}
		}
		if (frame_for_anm <= 4 * FRAME_INTERVAL){
			top = 384;
			left = 256 + (frame_for_anm - 1) / FRAME_INTERVAL * 64;
		}
		else if (frame_for_anm > 4 * FRAME_INTERVAL && frame_for_anm <= 5 * FRAME_INTERVAL){
			left = 384;
			top = 256;
		}
		else if (frame_for_anm > 5 * FRAME_INTERVAL && frame_for_anm <= 6 * FRAME_INTERVAL){
			left = 448;
			top = 256;
		}
		else if (frame_for_anm > 6 * FRAME_INTERVAL && frame_for_anm <= 7 * FRAME_INTERVAL){
			left = 384;
			top = 320;
		}
		else if (frame_for_anm > 7 * FRAME_INTERVAL && frame_for_anm <= 8 * FRAME_INTERVAL){
			left = 448;
			top = 320;
		}
		if (vx > 0){
			prev_direction = RIGHT;
		}
		else{
			prev_direction = LEFT;
			SetReversalX(x);
		}
	}

	SetImgRect(left, top, left + width, top + height);
	DrawImg(x, y, 64, DRAW_CENTERED);
}

void ButterFly::CommonDestroy(){
	THFog *fog1 = NULL, *fog2 = NULL;
	THMaple *maples[8];

	fog1 = new THEnemyFog(ENEMY_FOG_BLUE1);
	fog2 = new THEnemyFog(ENEMY_FOG_BLUE2);
	for (int i = 0; i < 8; i++){
		int random = Random(0, 1);
		if (random == 0){
			maples[i] = new THMaple(MAPLE_BLUE, ROTATION_CLOCKWISE, 60, Random(1, 10), Random(0, 360));
		}
		else{
			maples[i] = new THMaple(MAPLE_BLUE, ROTATION_ANTICLOCKWISE, 60, Random(1, 10), Random(0, 360));
		}
	}

	fog1->SetPosition(x, y);
	fog2->SetPosition(x, y);
	AddRenderObject(fog1);
	AddRenderObject(fog2);
	for (int i = 0; i < 8; i++){
		maples[i]->SetPosition(x, y);
		maples[i]->SetVelocity(Random(1, 3));
		maples[i]->SetAngle(Random(0, 360));
		AddRenderObject(maples[i]);
	}
	Destroy();
}