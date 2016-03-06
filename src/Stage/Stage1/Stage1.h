#ifndef STAGE1_H
#define STAGE1_H

#include "../../THEngine/THEngine.h"

class Stage1 :public THStage{
private:
	int vbFloor;
	int texFloor;
public:
	Stage1();
	virtual ~Stage1();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

#endif