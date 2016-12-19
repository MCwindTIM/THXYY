#pragma once

#include "Bullet.h"

class LinDan : public BulletDelegate
{
public:
	LinDan(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class SmallJade : public BulletDelegate
{
public:
	SmallJade(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class Chain : public BulletDelegate
{
public:
	Chain(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class Rice : public BulletDelegate
{
public:
	Rice(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class ChongDan : public BulletDelegate
{
public:
	ChongDan(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class ZhaDan : public BulletDelegate
{
public:
	ZhaDan(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class Bacilli : public BulletDelegate
{
public:
	Bacilli(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class StarBulletSmall : public BulletDelegate
{
public:
	StarBulletSmall(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class PointBullet : public BulletDelegate
{
public:
	PointBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class NeedleBullet : public BulletDelegate
{
public:
	NeedleBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class BacteriaBullet : public BulletDelegate
{
public:
	BacteriaBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class StarBulletBig : public BulletDelegate
{
public:
	StarBulletBig(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class MidJade : public BulletDelegate
{
public:
	MidJade(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class ButterflyBullet : public BulletDelegate
{
public:
	ButterflyBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class KnifeBullet : public BulletDelegate
{
public:
	KnifeBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class EllipseBullet : public BulletDelegate
{
public:
	EllipseBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class DiDan : public BulletDelegate
{
public:
	DiDan(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class HeartBullet : public BulletDelegate
{
public:
	HeartBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class ArrowBullet : public BulletDelegate
{
public:
	ArrowBullet(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};

class BigJade : public BulletDelegate
{
public:
	BigJade(Bullet* bullet) : BulletDelegate(bullet) {}
	virtual bool Hit(float xPlayer, float yPlayer, float radius) override;
};