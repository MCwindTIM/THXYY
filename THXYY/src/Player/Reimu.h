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

	Vector2f subPlaneOffsetHigh[4][4];
	Vector2f subPlaneOffsetLow[4][4];

public:
	Reimu();
	virtual ~Reimu();

	virtual void Update() override;

	virtual void Fire() override;
	virtual void Bomb() override;

	virtual void OnEnterLowSpeed() override;
	virtual void OnEnterHighSpeed() override;
	virtual void OnPowerLevelChanged(int oldPowerLevel, int newPowerLevel) override;
	virtual void SetupSubPlanes() override;
};

#endif