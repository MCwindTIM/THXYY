#pragma once

#include "Item.h"

class ScoreItem : public Item
{
public:
	ScoreItem();
	virtual ~ScoreItem();

	virtual void OnGot() override;
};