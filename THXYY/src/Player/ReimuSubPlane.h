#ifndef REIMU_SUBPLANE_H
#define REIMU_SUBPLANE_H

#include "Reimu.h"

class ReimuSubPlane : public SubPlane
{
private:
	static const float ROTATION_SPEED;
	int frame_shoot = 0;

public:
	ReimuSubPlane();
	virtual ~ReimuSubPlane();

	virtual void Update() override;

	virtual void Fire() override;
};

#endif