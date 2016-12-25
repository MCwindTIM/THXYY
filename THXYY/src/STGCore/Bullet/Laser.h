#ifndef LASER_H
#define LASER_H

#include <THEngine.h>

using namespace THEngine;

class Laser : public Sprite
{
public:
	enum LaserColor
	{
		RED,
		PURPLE,
		BLUE,
		TEAL,
		GREEN,
		YELLOW,
		ORANGE,
		GREY
	};

private:
	LaserColor laserColor;
	int warningTime;   //Ô¤¾¯Ê±¼ä

public:
	Laser();
	virtual ~Laser();

	virtual void Update() override;

	inline LaserColor GetLaserColor() { return laserColor; }

	inline void SetWarningTime(int warningTime) { this->warningTime = warningTime; }
	inline int GetWarningTime() { return warningTime; }
};

#endif