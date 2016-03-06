#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "THEngine\THEngine.h"

class ReimuBullet2 :public THPlayerBullet{
public:
	ReimuBullet2();
	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual bool Hit(float l, float t, float r, float b);
};

#endif