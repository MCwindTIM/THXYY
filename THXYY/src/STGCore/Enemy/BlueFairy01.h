#ifndef BLUEFAIRY01_H
#define BLUEFAIRY01_H

#include "Enemy.h"

class BlueFairy01 : public Enemy
{
private:
	enum MotionState
	{
		STATIC,
		LEFT,
		RIGHT
	};

	MotionState motionState;

	int frameForAnim;

public:
	BlueFairy01();
	virtual ~BlueFairy01();

	virtual void Update() override;
};

#endif