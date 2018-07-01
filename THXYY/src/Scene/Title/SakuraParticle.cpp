#include "SakuraParticle.h"
#include "../../STGCore/STGResources.h"

SakuraParticle::SakuraParticle()
{
	InitWithType(0);
}

SakuraParticle::SakuraParticle(int type)
{
	InitWithType(type);
}

SakuraParticle::~SakuraParticle()
{
}

void SakuraParticle::InitWithType(int type)
{
	auto stgResources = STGResources::GetInstance();

	SetTexture(stgResources->texEffBase);

	switch (type)
	{
	case 0:
		SetTexRect(Rect(0, 32, 224, 256));
		break;
	case 1:
		SetTexRect(Rect(32, 64, 224, 256));
		break;
	case 2:
		SetTexRect(Rect(192, 224, 224, 256));
		break;
	}
}

void SakuraParticle::Update()
{
	Sprite3D::Update();
}