#ifndef TITLE_H
#define TITLE_H

#include <THEngine.h>

using namespace THEngine;

class Title : public Scene
{
private:
	Layer* bgrLayer;
	Texture* titleTex;

	Layer* blackLayer = nullptr;
	Sprite* black = nullptr;

public:
	Title();
	virtual ~Title();
};

#endif