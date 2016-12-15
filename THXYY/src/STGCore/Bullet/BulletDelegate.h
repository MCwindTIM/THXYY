#pragma once

#include "Bullet.h"

class LinDan : public BulletDelegate
{
public:
	LinDan(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};