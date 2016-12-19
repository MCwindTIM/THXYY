#ifndef ENEMY_H
#define ENEMY_H

#include <THEngine.h>

using namespace THEngine;

class Enemy : public Sprite
{
public:
	enum EnemyColor
	{
		RED,
		YELLOW,
		GREEN,
		BLUE
	};

	enum ItemType
	{
		POWER_SMALL,
		SCORE
	};

	enum MotionState
	{
		STATIC,
		LEFT,
		RIGHT,
		STATIC_TO_LEFT,
		STATIC_TO_RIGHT,
		LEFT_TO_STATIC,
		RIGHT_TO_STATIC
	};

	static const int ANIM_INTERVAL = 6;

private:
	MotionState prevMotionState = STATIC;
	float prevX;

protected:
	float life;
	int score;
	float hitRange;
	EnemyColor enemyColor = BLUE;

	int powerItemSmallNum = 0;
	int scoreItemNum = 0;

	int frameForAnim = 0;

	MotionState motionState = STATIC;
	
private:
	void UpdateMotionState();

public:
	Enemy();
	virtual ~Enemy();

	virtual void OnDie();
	virtual void OnDestroy() override;

	virtual void Update() override;

	virtual void OnHitten(float damage);

	void DropItems();

	void SetItem(ItemType type, int count);

	inline void SetPosition(float x, float y)
	{
		Sprite::SetPosition(Vector3f(x, y, 40.0f));
	}

	inline void SetHitRange(float hitRange) { this->hitRange = hitRange; }
	inline float GetHitRange() { return hitRange; }
};

#endif