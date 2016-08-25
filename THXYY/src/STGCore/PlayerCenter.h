#ifndef PLAYERCENTER_H
#define PLAYERCENTER_H

#include <THEngine.h>

using namespace THEngine;

class PlayerCenter : public Sprite
{
private:
	enum State
	{
		ARISE,
		NORMAL,
		DISAPPEAR
	};

	State state;

	static const int ARISE_TIME = 15;
	static const int DISAPPEAR_TIME = 15;

public:
	PlayerCenter();
	virtual ~PlayerCenter();

	virtual void Update() override;

	void Disappear();
};

#endif