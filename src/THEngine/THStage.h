#ifndef STAGE_H
#define STAGE_H

class THStage {
protected:
	int frame;
public:
	THStage();
	virtual void CommonUpdate();
	virtual void CommonDraw();
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif