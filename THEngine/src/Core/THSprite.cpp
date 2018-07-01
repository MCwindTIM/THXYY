#include "THSprite.h"
#include "THGame.h"
#include <Math\THMath.h>
#include <Asset\THTexture.h>
#include <Renderer\THRenderPipeline.h>
#include <Renderer\THSpriteRenderer.h>

using namespace THEngine;

Sprite::Sprite()
{
	texRect = Rect(0, 0, 0, 0);
	alpha = 1.0f;
	color = Vector3f(1.0f, 1.0f, 1.0f);
	pivot = Vector2f(0.5f, 0.5f);
	rotation = 0;

	speed = 0;
	angle = 0;
	acSpeed = 0;
	acAngle = 0;

	flipX = false;
	flipY = false;
}

Sprite::~Sprite()
{
}

void Sprite::SetTexture(Ptr<Texture> texture)
{
	this->texture = texture;
}

void Sprite::SendToRenderQueue()
{
	Game::GetInstance()->GetRenderPipeline()->SendToRenderQueue(RenderPipeline::SPRITE, this);
}

void Sprite::Update()
{
	GameObject::Update();

	speed += acSpeed;
	angle += acAngle;
	vx = speed * cos(angle / 180.0f * Math::PI);
	vy = speed * sin(angle / 180.0f * Math::PI);
	vx += ax;
	vy += ay;
	position.x += vx;
	position.y += vy;
}

void Sprite::Draw()
{
	Game::GetInstance()->GetRenderPipeline()->GetSpriteRenderer()->Render(this);
}

void Sprite::GetWorldMatrix(Matrix* matrix)
{
	Matrix::Identity(matrix);

	if (this->flipX)
	{
		matrix->Set(0, 0, -1);
	}
	if (this->flipY)
	{
		matrix->Set(1, 1, -1);
	}

	Matrix temp;
	Matrix::Scale(&temp, GetScaleX(), GetScaleY(), 1.0f);
	*matrix *= temp;

	Matrix::RotateZ(&temp, this->rotation);
	*matrix *= temp;

	Matrix::Translate(&temp, this->position.x, this->position.y, this->position.z);
	*matrix *= temp;
}