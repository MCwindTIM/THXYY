#ifndef REIMU_H
#define REIMU_H

#include "../STGCore/STGCore.h"

class Reimu : public Player
{
private:
	int frame;

	MotionState prevState;

public:
	Reimu();
	virtual ~Reimu();

	virtual void Update() override;

	virtual void Fire() override;
	virtual void Bomb() override;
};

#endif