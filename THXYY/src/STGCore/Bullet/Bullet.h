#ifndef BULLET_H
#define BULLET_H

#include <THEngine.h>

using namespace THEngine;

class Bullet;

class BulletDelegate : public Object
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

protected:
	Bullet* bullet;

public:
	BulletDelegate(Bullet* bullet);
	virtual ~BulletDelegate();

	virtual bool Hit(float xPlayer, float yPlayer, float radius) = 0;
	virtual Rect GetTexRect() = 0;
	virtual Texture* GetTexture() = 0;
	virtual BulletColor GetBulletColor() = 0;
};

class Bullet : public Sprite
{
public:
	typedef BulletDelegate::BulletColor BulletColor;
	static const BulletColor RED = BulletColor::RED;
	static const BulletColor PURPLE = BulletColor::PURPLE;
	static const BulletColor BLUE = BulletColor::BLUE;
	static const BulletColor TEAL = BulletColor::TEAL;
	static const BulletColor GREEN = BulletColor::GREEN;
	static const BulletColor YELLOW = BulletColor::YELLOW;
	static const BulletColor GREY = BulletColor::GREY;
	static const BulletColor BRIGHT_GREY = BulletColor::BRIGHT_GREY;

	enum Type
	{
		NONE = 0,
		LINDAN_RED = 1,
		LINDAN_PURPLE = 2
	};

protected:
	BulletDelegate* bulletDelegate;
	Type type;
	BulletColor bulletColor;

	bool dirSame;                //朝向与运动方向相同
	bool autoDelete;             //出屏即消

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
};

#endif