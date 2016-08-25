#ifndef TITLE_H
#define TITLE_H

#include <THEngine.h>

using namespace THEngine;

class Title : public Scene
{
private:
	Layer* bgrLayer;
	Texture* titleTex;

public:
	Title();
	virtual ~Title();
};

#endif