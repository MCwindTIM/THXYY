#ifndef REIMU_SUBPLANE_H
#define REIMU_SUBPLANE_H

#include "Reimu.h"

class ReimuSubPlane : public Sprite
{
private:
	static const float ROTATION_SPEED;

public:
	ReimuSubPlane();
	virtual ~ReimuSubPlane();

	virtual void Update() override;
};

#endif