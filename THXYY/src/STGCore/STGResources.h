#ifndef STGRESOURCES_H
#define STGRESOURCES_H

#include <THEngine.h>

using namespace THEngine;

class STGResources : public Object
{
public:
	static STGResources* instance;

	static STGResources* GetInstance();

	Texture* texPlayerCenter;
	Texture* texEnemy01;
	Texture* texBullet01;

	Sound* soundShoot1 = nullptr;
	Sound* soundBiu = nullptr;

private:
	STGResources();

public:
	virtual ~STGResources();

	bool LoadTexTures();
	void UnloadTextures();

	bool LoadSounds();
	void UnloadSounds();
};

#endif