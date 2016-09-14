#pragma once

#include "Item.h"

class PowerItemSmall : public Item
{
public:
	PowerItemSmall();
	virtual ~PowerItemSmall();

	virtual void OnGot() override;
};