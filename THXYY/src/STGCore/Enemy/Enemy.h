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

protected:
	float life;
	int score;
	float hitRange;
	EnemyColor enemyColor = BLUE;

	int powerItemSmallNum = 0;
	int scoreItemNum = 0;


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