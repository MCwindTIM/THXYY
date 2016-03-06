#ifndef PLAYER_H
#define PLAYER_H

#include "THEngine\THEngine.h"

class Reimu :public THPlayer
{
public:
	Reimu();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Fire();
};

#endif