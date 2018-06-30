#ifndef TH_FIRST_PERSON_CAMERA_H
#define TH_FIRST_PERSON_CAMERA_H

#include <Core\THCamera.h>

namespace THEngine
{
	class FirstPersonCamera : public Camera3D
	{
	private:
		bool hasFocusLastFrame = true;
		Vector2f mousePosLastFrame;
		Vector3f lookDirLastFrame;
		Vector3f rightLastFrame;
		double sensitivity = 1;

		float rotationXZ = 0;
		float rotationY = 0;
		float walkSpeed = 0.05f;

	public:
		virtual void OnStart() override;
		virtual void Update() override;

		void SetSensitivity(double sensitivity) { this->sensitivity = sensitivity; }

		void SetWalkSpeed(float walkSpeed) { this->walkSpeed = walkSpeed; }
	};
}

#endif
