#include "THFirstPersonCamera.h"
#include <Platform\THInput.h>
#include <Core\THGame.h>

namespace THEngine
{
	void FirstPersonCamera::OnStart()
	{
		Camera3D::OnStart();

		::ShowCursor(SW_HIDE);

		auto input = Input::GetInstance();
		Vector2f mousePos;
		input->GetMousePosition(&mousePos);

		this->mousePosLastFrame = mousePos;
		this->lookDirLastFrame = this->GetLookAt() - this->GetPosition();
		this->rightLastFrame = Vector3f::Cross(this->GetUp(), this->lookDirLastFrame);
	}

	void FirstPersonCamera::Update()
	{
		Camera3D::Update();

		auto input = Input::GetInstance();
		if (input->HasFocus() == false)
		{
			this->hasFocusLastFrame = false;
			return;
		}

		if (this->hasFocusLastFrame == false)
		{
			OnStart();
			this->hasFocusLastFrame = true;
			return;
		}

		Vector2f mousePos;
		if (input->GetMousePosition(&mousePos) == false)
			return;

		// lock mouse position
		if (input->SetMousePosition(this->mousePosLastFrame) == false)
			return;

		bool changed = false;

		Vector2f delta = mousePos - this->mousePosLastFrame;
		delta *= this->sensitivity;

		this->rotationXZ += delta.x;
		this->rotationY += delta.y;
		if (this->rotationY > 90)
			this->rotationY = 90;
		else if (this->rotationY < -90)
			this->rotationY = -90;

		Quaternion qx, qy;
		Quaternion::RotateAngleAxis(&qx, Vector3f(0, 1, 0), this->rotationXZ);
		Quaternion::RotateAngleAxis(&qy, Vector3f(1, 0, 0), this->rotationY);

		Quaternion q = qy * qx;

		SetUp(Vector3f(0, 1, 0) * q);
		this->lookDirLastFrame = Vector3f(0, 0, 1) * q;
		this->rightLastFrame = Vector3f(1, 0, 0) * q;
		changed = true;

		if (input->KeyDown(DIK_W))
		{
			changed = true;
			this->position += this->lookDirLastFrame * this->walkSpeed;
		}
		else if (input->KeyDown(DIK_A))
		{
			changed = true;
			this->position -= this->rightLastFrame * this->walkSpeed;
		}
		else if (input->KeyDown(DIK_D))
		{
			changed = true;
			this->position += this->rightLastFrame * this->walkSpeed;
		}
		else if (input->KeyDown(DIK_S))
		{
			changed = true;
			this->position -= this->lookDirLastFrame * this->walkSpeed;
		}

		if (changed)
		{
			SetLookAt(GetPosition() + this->lookDirLastFrame);
		}
	}
}