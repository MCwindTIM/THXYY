#ifndef REIMU_SUBPLANE_BULLET_H
#define REIMU_SUBPLANE_BULLET_H

#include <STGCore.h>

class ReimuSubPlaneBullet : public PlayerBullet
{
private:
	Enemy* target = nullptr;

public:
	ReimuSubPlaneBullet();
	virtual ~ReimuSubPlaneBullet();

	virtual void Update() override;
};

#endif