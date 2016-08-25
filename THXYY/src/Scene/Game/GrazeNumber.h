#ifndef GRAZENUMBER_H
#define GRAZENUMBER_H

#include <THEngine.h>

using namespace THEngine;

class GrazeNumber : public Sprite
{
private:
	int number;

public:
	virtual void Update() override;

	inline void SetNumber(int number) { this->number = number; }
};

#endif