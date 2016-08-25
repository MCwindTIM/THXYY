#pragma once

#include "Bullet.h"

class LinDan : public BulletDelegate
{
public:
	LinDan(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual Texture* GetTexture() override;
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class LinDanRed : public LinDan
{
public:
	LinDanRed(Bullet* bullet) : LinDan(bullet) {}
	virtual Rect GetTexRect() override;
	virtual BulletColor GetBulletColor() override;
};

class LinDanPurple : public LinDan
{
public:
	LinDanPurple(Bullet* bullet) : LinDan(bullet) {}
};
