#ifndef SCORENUMBER_H
#define SCORENUMBER_H

#include <THEngine.h>

using namespace THEngine;

class ScoreNumber : public Sprite
{
private:
	int number;

public:
	virtual void Update() override;

	inline void SetNumber(int number) { this->number = number; }
};

#endif