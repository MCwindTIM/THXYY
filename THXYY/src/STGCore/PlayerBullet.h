#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include <THEngine.h>

using namespace THEngine;

class PlayerBullet : public Sprite
{
protected:
	float damage;
	float hitRange;

public:
	PlayerBullet();
	virtual ~PlayerBullet();

	virtual void Update() override;

	inline void SetPosition(float x, float y)
	{
		Sprite::SetPosition(Vector3f(x, y, 80.0f));
	}

	inline void SetDamage(float damage) { this->damage = damage; }
	inline float GetDamage() { return damage; }

	inline void SetHitRange(float hitRange) { this->hitRange = hitRange; }
	inline float GetHitRange() { return hitRange; }
};

#endif