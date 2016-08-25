#include "Reimu.h"

static const int ANIM_INTERVAL = 5;
static const int TURN_INTERVAL = 2;

Reimu::Reimu()
{
	auto manager = AssetManager::GetInstance();

	frame = 0;

	SetTexture(manager->CreateTextureFromFile("res/player/reimu.png"));

	SetHiSpeed(4.5f);
	SetLowSpeed(1.5f);
}

Reimu::~Reimu()
{
	auto manager = AssetManager::GetInstance();
	manager->DestroyTexture(texture);
}

void Reimu::Update()
{
	Player::Update();

	frame++;

	if (motionState == STATIC || motionState == UP || motionState == DOWN)
	{
		if (frame >= 8 * ANIM_INTERVAL)
		{
			frame = 0;
		}
		int left = 32 * (frame / ANIM_INTERVAL);
		SetTexRect(Rect(left, left + 32, 0, 48));
	}
	else
	{
		if (motionState == LEFT || motionState == LEFT_UP || motionState == LEFT_DOWN)
		{
			if (prevState == STATIC || prevState == UP || prevState == DOWN)
			{
				frame = 0;
			}
			if (frame >= 8 * ANIM_INTERVAL)
			{
				frame = 4 * ANIM_INTERVAL;
			}
			int left = 32 * (frame / ANIM_INTERVAL);
			SetTexRect(Rect(left, left + 32, 48, 96));
		}
		else if (motionState == RIGHT || motionState == RIGHT_UP || motionState == RIGHT_DOWN)
		{
			if (prevState == STATIC || prevState == UP || prevState == DOWN)
			{
				frame = 0;
			}
			if (frame >= 4 * ANIM_INTERVAL + 4 * TURN_INTERVAL)
			{
				frame = 4 * TURN_INTERVAL;
			}

			int left;

			if (frame < 4 * TURN_INTERVAL)
			{
				left = 32 * (frame / TURN_INTERVAL);
			}
			else
			{
				left = 32 * ((frame - 4 * TURN_INTERVAL) / ANIM_INTERVAL) + 128;
			}
			SetTexRect(Rect(left, left + 32, 96, 144));
		}
	}
	prevState = motionState;
}

void Reimu::Fire()
{

}

void Reimu::Bomb()
{

}