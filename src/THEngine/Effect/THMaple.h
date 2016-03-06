#ifndef THMAPLE_H
#define THMAPLE_H

#include "../RenderObject.h"
#include "../THCommon.h"
#include "../Engine_Core.h"

#define MAPLE_RED                                        1
#define MAPLE_GREEN                                    2
#define MAPLE_BLUE                                      3
#define MAPLE_YELLOW                                 4
#define MAPLE_DEFAULT                                5

#define ROTATION_CLOCKWISE                     1
#define ROTATION_ANTICLOCKWISE              2

class THMaple :public RenderObject{
private:
	int life;
	int frame;
	BYTE RotationDir;
	BYTE type;
	float vRotation;
	float rot;
public:
	THMaple(){}
	THMaple(BYTE type, BYTE RotationDir, int life, float vRotation, float rot) :
		type(type), RotationDir(RotationDir), life(life), vRotation(vRotation), rot(rot){
		Init();
	}
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

#endif