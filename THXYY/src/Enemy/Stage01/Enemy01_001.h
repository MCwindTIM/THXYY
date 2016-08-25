#pragma once

#include "../../STGCore/STGCore.h"

class Enemy01_001 : public BlueFairy01
{
private:
	int frame;

public:
	Enemy01_001();
	virtual ~Enemy01_001();

	virtual void Update() override;
};