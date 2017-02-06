#ifndef REIMU_H
#define REIMU_H

#include "../STGCore/STGCore.h"

class ReimuSubPlane;

class Reimu : public Player
{
private:
	int frame;
	int frame_fire = 0;

	MotionState prevState;

	ReimuSubPlane* subPlanes[4];

public:
	Reimu();
	virtual ~Reimu();

	virtual void Update() override;

	virtual void Fire() override;
	virtual void Bomb() override;
};

#endif