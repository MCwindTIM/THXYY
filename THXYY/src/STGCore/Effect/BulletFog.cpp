#include "BulletFog.h"
#include "../STGResources.h"
#include "../STGEngine.h"

static const int LIFE_TIME = 15;
static const int ARISE_TIME = 8;
static const float INITIAL_ALPHA = 0.0f;

BulletFog::BulletFog(Bullet* bullet)
{
	auto texManager = STGResources::GetInstance();

	this->bullet = bullet;
	this->bullet->Retain();

	SetTexture(texManager->texBullet01);

	SetPosition(Vector3f(bullet->GetPosition().x, bullet->GetPosition().y, 2.0f));

	SetAlpha(INITIAL_ALPHA);

	switch (bullet->GetBulletColor())
	{
	case Bullet::GREY:
		SetTexRect(Rect(1, 31, 209, 239));
		break;
	case Bullet::RED:
		SetTexRect(Rect(33, 63, 209, 239));
		break;
	case Bullet::PURPLE:
		SetTexRect(Rect(65, 95, 209, 239));
		break;
	case Bullet::BLUE:
		SetTexRect(Rect(97, 127, 209, 239));
		break;
	case Bullet::TEAL:
		SetTexRect(Rect(129, 159, 209, 239));
		break;
	case Bullet::GREEN:
		SetTexRect(Rect(161, 191, 209, 239));
		break;
	case Bullet::YELLOW:
		SetTexRect(Rect(193, 223, 209, 239));
		break;
	case Bullet::BRIGHT_GREY:
		SetTexRect(Rect(225, 255, 209, 239));
		break;
	default:
		SetTexRect(Rect(0, 0, 0, 0));
		break;
	}
}

BulletFog::~BulletFog()
{
	TH_SAFE_RELEASE(bullet);
}

void BulletFog::Update()
{
	Sprite::Update();

	frame++;

	if (frame <= ARISE_TIME)
	{
		alpha += (1.0f - INITIAL_ALPHA) / ARISE_TIME;
	}
	else
	{
		SetScaleX(GetScaleX() - 0.5f / (LIFE_TIME - ARISE_TIME));
		SetScaleY(GetScaleY() - 0.5f / (LIFE_TIME - ARISE_TIME));
	}

	if (frame == LIFE_TIME)
	{
		MarkDestroy();
		STGEngine::GetInstance()->AddBullet(bullet);
	}
}
