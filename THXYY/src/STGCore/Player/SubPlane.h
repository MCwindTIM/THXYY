#ifndef SUBPLANE_H
#define SUBPLANE_H

#include <THEngine.h>

using namespace THEngine;

class SubPlane : public Sprite
{
public:
	SubPlane();
	virtual ~SubPlane();

	virtual void Update() override;

	virtual void Fire() = 0;

	void Disappear();
};

#endif