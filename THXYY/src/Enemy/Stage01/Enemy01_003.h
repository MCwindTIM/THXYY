#ifndef ENEMY01_003_H
#define ENEMY01_003_H

#include "../../STGCore/STGCore.h"

class Enemy01_003 : public ButterFly
{
	int frame = 0;

public:
	Enemy01_003();
	virtual ~Enemy01_003();

	virtual void Update() override;
};

#endif