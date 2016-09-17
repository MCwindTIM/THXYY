#pragma once

#include <THEngine.h>

using namespace THEngine;

class ParticleLayer : public Layer
{
private:
	int frame = 0;

public:
	ParticleLayer();
	virtual ~ParticleLayer();

	virtual void Update() override;
};