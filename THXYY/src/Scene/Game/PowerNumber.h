#ifndef POWERNUMBER_H
#define POWERNUMBER_H

#include <THEngine.h>

using namespace THEngine;

class PowerNumber : public Sprite
{
private:
	int number;

public:
	virtual void Update() override;

	inline void SetNumber(int number) { this->number = number; }
};

#endif