#include "THParticle3D.h"
#include "../Core/THGame.h"

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
		Game::GetInstance()->SendToRenderQueue(Game::SPRITE, this);
	}

	void Particle3D::RotateByAxis(Vector3f axis, float degree)
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
		Game::GetInstance()->GetParticle3DRenderer()->Render(this);
	}
}