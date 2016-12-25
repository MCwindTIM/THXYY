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
	Texture* texBullet02 = nullptr;
	Texture* texBullet03 = nullptr;
	Texture* texBullet04 = nullptr;
	Texture* texReimu;
	Texture* texEffBase;
	Texture* texPointLight;
	Texture* texFourAngleStar = nullptr;

	Sound* soundShoot1 = nullptr;
	Sound* soundShoot2 = nullptr;
	Sound* soundShoot3 = nullptr;
	Sound* soundBiu = nullptr;
	Sound* soundMenuOK = nullptr;
	Sound* soundMenuSelect = nullptr;
	Sound* soundItem = nullptr;
	Sound* soundDamage00 = nullptr;
	Sound* soundDamage01 = nullptr;
	Sound* soundEnemyDie00 = nullptr;
	Sound* soundEnemyDie01 = nullptr;
	Sound* soundPlayerShoot = nullptr;
	Sound* soundBomb = nullptr;
	Sound* soundExplode = nullptr;

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