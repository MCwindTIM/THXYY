#ifndef ENEMY1_H
#define ENEMY1_H

#include "stdafx.h"
#include "../../THEngine/THEngine.h"

class Enemy1_001 :public BlueFairy2{
public:
	Enemy1_001();
	virtual void Init();
	virtual void Update();
	virtual void Destroy();
};

class Enemy1_002 :public RedFairy2{
public:
	Enemy1_002();
	virtual void Init();
	virtual void Update();
	virtual void Destroy();
};

class Enemy1_003 :public ButterFly{
public:
	Enemy1_003();
	virtual void Init();
	virtual void Update();
	virtual void Destroy();
};

class EnemyTest :public ButterFly{
public:
	EnemyTest();
	virtual void Init();
	virtual void Update();
	virtual void Destroy();
};

#endif