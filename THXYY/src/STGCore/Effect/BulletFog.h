#pragma once

#include <THEngine.h>
#include "../Bullet/Bullet.h"

using namespace THEngine;

class BulletFog : public Sprite
{
protected:
	int frame = 0;
	Bullet* bullet = nullptr;

public:
	BulletFog(Bullet* bullet);
	virtual ~BulletFog();

	virtual void Update() override;
};