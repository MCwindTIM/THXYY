#ifndef THITEM_H
#define THITEM_H

#include "RenderObject.h"

#define ITEM_POWER_SMALL        1

class THItem :public RenderObject{
public:
	THItem();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void CommonUpdate();
	virtual void CommonDraw();
	virtual bool Hit(float x, float y) = 0;
	virtual void Effect() = 0;
};

class PowerItemSmall :public THItem{
public:
	PowerItemSmall();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual bool Hit(float x, float y);
	virtual void Effect();
};

#endif