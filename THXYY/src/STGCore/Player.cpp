#include "Player.h"
#include "STGEngine.h"

static const int DYING_TIME = 12;
static const int SHRINK_TIME = 3;

Player::Player()
{
	center = nullptr;
	isHiSpeed = true;
	state = NORMAL;
	frame_counter = 0;
	determineDeathTime = 9;
	radius = 3.0f;
	invincible = false;
}

Player::~Player()
{

}

void Player::Update()
{
	auto input = Input::GetInstance();
	auto engine = STGEngine::GetInstance();
	auto scene = engine->GetGameScene();

	if (invincible)
	{
		frame_invincible--;
		if (frame_invincible < 0)
		{
			invincible = false;
			SetColor(Vector3f(1.0f, 1.0f, 1.0f));
		}
		else
		{
			//¼ÆËãÉÁË¸Ð§¹û
			invincible_shrink_counter++;
			if (invincible_shrink_counter == 2 * SHRINK_TIME)
			{
				invincible_shrink_counter = 0;
			}
			if (invincible_shrink_counter >= SHRINK_TIME && invincible_shrink_counter < 2 * SHRINK_TIME)
			{
				SetColor(Vector3f(0.4f, 0.4f, 0.4f));
			}
			else
			{
				SetColor(Vector3f(1.0f, 1.0f, 1.0f));
			}
		}
	}

	if (state == NORMAL)
	{
		Move();

		if (input->KeyDown(DIK_Z))
		{
			Fire();
		}

		int bomb = engine->GetBomb();
		if (input->KeyDown(DIK_X))
		{
			if (bomb >= 1)
			{
				engine->SetBomb(bomb - 1);
				Bomb();
			}
		}
	}
	else if (state == DETERMINE_DEATH)
	{
		SetSpeed(0);
		frame_counter++;
		if (frame_counter > determineDeathTime)
		{
			Biu();
		}
		else if (input->KeyDown(DIK_X))
		{
			int bomb = engine->GetBomb();
			if (bomb >= 1)
			{
				engine->SetBomb(bomb - 1);
				state = NORMAL;
				Bomb();
			}
		}
	}
	else if (state == DYING)
	{
		if (alpha <= 0)
		{
			state = REINTERING;
			SetPosition(192.0f, -32.0f);
			SetSpeed(1.2f);
			SetAngle(90.0f);
			SetAlpha(1.0f);
			SetInvincible(250);

			auto life = engine->GetLife();
			if (life > 0)
			{
				engine->SetLife(life - 1);
			}
			else
			{
				engine->GameOver();
			}
		}
		else
		{
			alpha -= 1.0f / DYING_TIME;
		}
	}
	else if (state == REINTERING)
	{
		if (position.y >= 48.0f)
		{
			position.y = 48.0f;
			state = NORMAL;
		}
	}

	Sprite::Update();

	if (position.x < 8.0f)
	{
		position.x = 8.0f;
	}
	if (position.x > 376.0f)
	{
		position.x = 376.0f;
	}
	if (position.y < 16.0f)
	{
		if (state != REINTERING)
		{
			position.y = 16.0f;
		}
	}
	if (position.y > 432.0f)
	{
		position.y = 432.0f;
	}
}

void Player::Move()
{
	auto input = Input::GetInstance();
	auto engine = STGEngine::GetInstance();
	auto scene = engine->GetGameScene();

	if (input->KeyDown(DIK_LSHIFT) || input->KeyDown(DIK_RSHIFT))
	{
		if (isHiSpeed)
		{
			center = new PlayerCenter();
			scene->GetSTGLayer()->AddChild(center);
		}
		SetSpeed(GetLowSpeed());
		isHiSpeed = false;
	}
	else
	{
		if (!isHiSpeed)
		{
			center->Disappear();
		}
		SetSpeed(GetHiSpeed());
		isHiSpeed = true;;
	}

	if (input->KeyDown(DIK_LEFT))
	{
		if (input->KeyDown(DIK_UP))
		{
			SetAngle(135.0f);
			motionState = LEFT_UP;
		}
		else if (input->KeyDown(DIK_DOWN))
		{
			SetAngle(-135.0f);
			motionState = LEFT_DOWN;
		}
		else
		{
			SetAngle(180.0f);
			motionState = LEFT;
		}
	}
	else if (input->KeyDown(DIK_RIGHT))
	{
		if (input->KeyDown(DIK_UP))
		{
			SetAngle(45.0f);
			motionState = RIGHT_UP;
		}
		else if (input->KeyDown(DIK_DOWN))
		{
			SetAngle(-45.0f);
			motionState = RIGHT_DOWN;
		}
		else
		{
			SetAngle(0.0f);
			motionState = RIGHT;
		}
	}
	else if (input->KeyDown(DIK_UP))
	{
		SetAngle(90.0f);
		motionState = UP;
	}
	else if (input->KeyDown(DIK_DOWN))
	{
		SetAngle(-90.0f);
		motionState = DOWN;
	}
	else
	{
		SetSpeed(0.0f);
		motionState = STATIC;
	}
}

void Player::Hitten()
{
	state = DETERMINE_DEATH;
	frame_counter = 0;

	STGResources::GetInstance()->soundBiu->Play();
}

void Player::Biu()
{
	state = DYING;

	auto engine = STGEngine::GetInstance();
	auto life = engine->GetLife();
}

bool Player::IsDamageable()
{
	return state == NORMAL && invincible == false;
}