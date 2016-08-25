#ifndef POINTNUMBER_H
#define POINTNUMBER_H

#include <THEngine.h>

using namespace THEngine;

class PointNumber : public Sprite
{
private:
	int number;

public:
	virtual void Update() override;

	inline void SetNumber(int number) { this->number = number; }
};

#endif