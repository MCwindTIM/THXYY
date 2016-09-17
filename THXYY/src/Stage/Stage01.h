#ifndef STAGE01_H
#define STAGE01_H

#include "../STGCore/STGCore.h"

class Stage01 : public Stage
{
private:
	int frame = 0;

public:
	Stage01();
	virtual ~Stage01();

	virtual void Update() override;
	virtual void UpdateBackground() override;
	virtual void OnLoad() override;
};

#endif