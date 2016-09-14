#pragma once

#include "../../STGCore/STGCore.h"

class Enemy01_001 : public BlueFairy01
{
private:
	int frame;
	float shootAngle = 0;
	float acShootAngle = 0;

public:
	Enemy01_001();
	virtual ~Enemy01_001();

	virtual void Update() override;
};