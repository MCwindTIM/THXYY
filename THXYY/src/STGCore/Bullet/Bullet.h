#ifndef BULLET_H
#define BULLET_H

#include <THEngine.h>

using namespace THEngine;

class Bullet;

class BulletDelegate : public Object
{
protected:
	Bullet* bullet;

public:
	BulletDelegate(Bullet* bullet);
	virtual ~BulletDelegate();

	virtual bool Hit(float xPlayer, float yPlayer, float radius) = 0;
};

class Bullet : public Sprite
{
public:
	enum BulletColor
	{
		GREY,
		RED,
		PURPLE,
		BLUE,
		TEAL,
		GREEN,
		YELLOW,
		BRIGHT_GREY
	};

	enum Type
	{
		NONE = 0,
		LINDAN_RED = 1,
		LINDAN_PURPLE = 2,
		LINDAN_BLUE = 3,
		LINDAN_TEAL = 4,
		LINDAN_GREEN = 5,
		LINDAN_YELLOW = 6,
		LINDAN_ORANGE = 7,
		LINDAN_GREY = 8
	};

protected:
	BulletDelegate* bulletDelegate;
	Type type;
	BulletColor bulletColor;

	bool dirSame;                //朝向与运动方向相同
	bool autoDelete = true;             //出屏即消

public:
	Bullet();
	virtual ~Bullet();

	inline bool Hit(float x, float y, float radius)
	{
		return bulletDelegate->Hit(x, y, radius);
	}

	inline void SetPosition(float x, float y)
	{
		Sprite::SetPosition(Vector3f(x, y, 5.0f));
	}

	inline void SetDirSame(bool dirSame) { this->dirSame = dirSame; }
	inline void SetAutoDelete(bool autoDelete) { this->autoDelete = autoDelete; }

	inline void SetBulletColor(BulletColor bulletColor) { this->bulletColor = bulletColor; }
	inline BulletColor GetBulletColor() { return bulletColor; }

	void SetType(Type type);

	virtual void Update() override;

	void OnDie();
};

#endif