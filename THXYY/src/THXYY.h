#ifndef THXYY_H
#define THXYY_H

#include "THEngine/THEngine.h"
#include "STGCore\STGCore.h"

using namespace THEngine;

class THXYY : public Game
{
private:
	STGEngine* engine;

public:
	THXYY();
	virtual ~THXYY();

	int CreateGame(int width, int height, bool fullScreen);

	virtual void OnShutdown() override;
};

#endif