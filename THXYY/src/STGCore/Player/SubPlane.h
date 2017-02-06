#ifndef SUBPLANE_H
#define SUBPLANE_H

#include "Player.h"

class SubPlane : public Sprite
{
public:
	SubPlane();
	virtual ~SubPlane();

	virtual void Update() override;

	virtual void Fire() = 0;
};

#endif