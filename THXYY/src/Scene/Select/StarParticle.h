#ifndef STAR_PARTICLE_H
#define STAR_PARTICLE_H

#include <THEngine.h>

using namespace THEngine;

class StarParticle : public Sprite3D
{
public:
	StarParticle();
	virtual ~StarParticle() = default;

	static Ptr<Texture> tex;
};

#endif