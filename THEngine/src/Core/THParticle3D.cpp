#include "THParticle3D.h"
#include "THGame.h"
#include <Asset\THTexture.h>
#include <Renderer\THRenderPipeline.h>
#include <Renderer\THParticle3DRenderer.h>

namespace THEngine
{
	Particle3D::Particle3D()
	{
	}

	Particle3D::~Particle3D()
	{
	}

	void Particle3D::SendToRenderQueue()
	{
		Game::GetInstance()->GetRenderPipeline()->SendToRenderQueue(RenderPipeline::SPRITE, this);
	}

	void Particle3D::RotateByAxis(const Vector3f& axis, float degree)
	{
		Quaternion temp;
		Quaternion::RotateAngleAxis(&temp, Vector3f(axis.x, axis.y, axis.z), degree);
		rotation3D *= temp;
	}

	void Particle3D::Update()
	{
		GameObject::Update();

		position = position + speed * direction;

		RotateByAxis(rotatingAxis, rotatingSpeed);

		life--;
		if (life < 0)
		{
			MarkDestroy();
		}
	}

	void Particle3D::Draw()
	{
		Game::GetInstance()->GetRenderPipeline()->GetParticle3DRenderer()->Render(this);
	}

	void Particle3D::GetWorldMatrix(Matrix* matrix)
	{
		Matrix& transform = *matrix;
		Matrix::Identity(&transform);

		if (this->flipX)
		{
			transform.Set(0, 0, -1);
		}
		if (this->flipY)
		{
			transform.Set(1, 1, -1);
		}

		Matrix temp;

		Matrix::Scale(&temp, GetScale().x, GetScale().y, GetScale().z);
		transform *= temp;

		transform *= this->rotation3D;

		Matrix::Translate(&temp, this->position.x, this->position.y,
			this->position.z);
		transform *= temp;
	}
}