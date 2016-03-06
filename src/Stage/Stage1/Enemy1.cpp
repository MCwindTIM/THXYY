#include "stdafx.h"
#include "Enemy1.h"

Enemy1_001::Enemy1_001()
{
	Init();
}

void Enemy1_001::Init()
{
	SetLife(10);
	SetAngle(45);
	SetUpdateType(UPDATETYPE_CS);
	SetVelocity(2);
	SetAcAngle(45);
	SetScore(1000);
}

void Enemy1_001::Update()
{
	if (frame > 60){
		angle -= 1;
		if (angle < 0){
			angle = 0;
		}
	}
	if (frame % 6 == 0 && frame % 30 <18){
		Shoot(x, y - 8, 3, GetAngleToPlayer(x, y), SMALLJADE_BLUE, 0);
	}
	UpdatePosition();
}

void Enemy1_001::Destroy()
{
	DropItem(x, y, ITEM_POWER_SMALL);
}

Enemy1_002::Enemy1_002()
{
	Init();
}

void Enemy1_002::Init()
{
	SetLife(10);
	SetAngle(135);
	SetUpdateType(UPDATETYPE_CS);
	SetVelocity(2);
	SetAcAngle(135);
	SetScore(1000);
}

void Enemy1_002::Update()
{
	if (frame > 60){
		angle += 1;
		if (angle >180){
			angle = 180;
		}
	}
	if (frame % 6 == 0 && frame % 30 <18){
		Shoot(x, y - 8, 3, GetAngleToPlayer(x, y), SMALLJADE_RED, 0);
	}
	UpdatePosition();
}

void Enemy1_002::Destroy()
{
	DropItem(x, y, ITEM_POWER_SMALL);
}

Enemy1_003::Enemy1_003(){
	Init();
}

void Enemy1_003::Init(){
	SetLife(100);
	SetAngle(90);
	SetUpdateType(UPDATETYPE_CS);
	SetVelocity(2);
	SetAcAngle(135);
	SetScore(5000);
}

void Enemy1_003::Update(){
	if (frame == 60){
		SetAcceleration(-0.05f);
		SetAcAngle(90);
	}
	if (frame == 100){
		SetAcceleration(0);
	}
	if (frame >= 120 && frame <= 400 && ((frame - 120) % 20 == 0)){
		float angle = GetAngleToPlayer(x, y);
		for (int i = 0; i < 4; i++){
			float angle2 = angle + 90 * i;
			for (int j = 0; j < 5; j++){
				Shoot(x, y, 3, angle2 - 20 + 10 * j, SMALLJADE_BLUE, 0);
			}
		}
	}
	if (frame == 420){
		SetAcceleration(0.05f);
	}
	if (frame == 440){
		SetAcceleration(0);
	}
	UpdatePosition();
}

void Enemy1_003::Destroy(){
	DropItem(x, y, ITEM_POWER_SMALL);
}

EnemyTest::EnemyTest(){
	Init();
}

void EnemyTest::Init(){
	SetLife(1000);
	SetAngle(90);
	SetUpdateType(UPDATETYPE_CS);
	SetVelocity(2);
	SetAcAngle(135);
	SetScore(5000);
}

void EnemyTest::Update(){
	if (frame == 60){
		SetAcceleration(-0.05f);
		SetAcAngle(90);
	}
	if (frame == 100){
		SetAcceleration(0);
	}
	if (frame >= 120 && frame % 2 == 0 && frame < 180){
		/*int a = Random(-20, 20);
		int b = Random(-20, 20);
		float v = Random(2, 3);
		int angle = Random(0, 360);
		for (int i = 0; i < 20; i++){
			Shoot(x + a, y + b, v, angle + 18 * i, SCALE_PURPLE, 0);
		}
		int a2 = Random(-20, 20);
		int b2 = Random(-20, 20);
		float v2 = Random(2, 3);
		int angle2 = Random(0, 360);
		for (int i = 0; i < 20; i++){
			Shoot(x + a2, y + b2, v2, angle2 + 18 * i, SCALE_GREEN, 0);
		}*/

		float xBul = x + (frame - 120);
		float yBul = y + (frame - 120);
		THBullet* bullet = CreateBullet(xBul, yBul, 
			0, GetAngleToPlayer(xBul,yBul), SCALE_RED, 0);
		THBulletEvent e;
		e.attributeType = ATTRIBUTE_SPEED;
		e.changeManner = CHANGEMANNER_LINEAR;
		e.changeTime = 30;
		e.firstOccurFrame = 120;
		e.changeType = CHANGETYPE_CHANGETO;
		e.repeatTime = 1;
		e.repeatFrameInterval = 1;
		e.value = 2;
		bullet->AddEvent(&e);
		ShootBullet(bullet);
	}
	UpdatePosition();
}

void EnemyTest::Destroy(){
	for (int i = 0; i < 6; i++){
		DropItem(x + Random(-10, 10), y + Random(-10, 10), ITEM_POWER_SMALL);
	}
}