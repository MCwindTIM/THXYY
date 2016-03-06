#ifndef THPLAYER_H
#define THPLAYER_H

#include "RenderObject.h"

/*************自机运动方向*****************/
#define DIRECTION_LEFT               1
#define DIRECTION_RIGHT              2
#define DIRECTION_UP                 3
#define DIRECTION_DOWN               4
#define DIRECTION_LEFT_AND_UP        5
#define DIRECTION_RIGHT_AND_UP       6
#define DIRECTION_LEFT_AND_DOWN      7
#define DIRECTION_RIGHT_AND_DOWN     8
#define DIRECTION_STABLE             9

class THPlayer :public RenderObject{
public:
	UINT  nPlayer;
	float   h_velocity;
	float   l_velocity;
	int power;
	int maxpower;
	float h_step;
	float h_step2;       //斜步
	float l_step;
	float l_step2;       //斜步
	UINT  direction;
	bool  bHigh;
	bool  bDead;
	bool bDamage;      //是否能够受到伤害
	int r;             //判定点半径
	UINT frame;
	UINT deadframe;
	UINT fireframe;
public:
	THPlayer();
	virtual ~THPlayer();
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Biu();
	virtual void Fire() = 0;
	inline void SetDead(bool dead){ bDead = dead; }
	inline bool IsDead(){ return bDead; }
	void SetPlayerDirection(UINT direction);
	inline void EnableDamage(){ bDamage = true; }
	inline void DisableDamage(){ bDamage = false; }
	inline bool IsDamageable(){ return bDamage; }
	inline int GetPower(){ return power; }
	inline void SetPower(int power){ this->power = power; }
	void Reset();
};

#endif