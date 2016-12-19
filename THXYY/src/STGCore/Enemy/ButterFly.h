#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include "Enemy.h"

class ButterFly : public Enemy
{
public:
	ButterFly();
	virtual ~ButterFly();

	virtual void Update() override;
};

#endif