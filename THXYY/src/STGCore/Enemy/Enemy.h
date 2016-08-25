#ifndef ENEMY_H
#define ENEMY_H

#include <THEngine.h>

using namespace THEngine;

class Enemy : public Sprite
{
protected:
	int life;
	int score;

public:
	Enemy();
	virtual ~Enemy();

	virtual void OnDie();
	virtual void OnDestroy() override;

	virtual void Update() override;

	inline void SetPosition(float x, float y)
	{
		Sprite::SetPosition(Vector3f(x, y, 40.0f));
	}
};

#endif