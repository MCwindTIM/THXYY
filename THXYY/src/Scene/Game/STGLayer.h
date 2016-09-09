#ifndef STGLAYER_H
#define STGLAYER_H

#include <THEngine.h>

using namespace THEngine;

class STGLayer : public Layer
{
public:
	STGLayer();
	virtual ~STGLayer();

	virtual void Update() override;

	virtual void OnDestroy() override;
};

#endif