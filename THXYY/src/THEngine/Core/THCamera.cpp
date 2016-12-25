#include "THCamera.h"
#include "../Asset/THAssetManager.h"

namespace THEngine
{
	Camera::Camera()
	{

	}

	Camera::Camera(const String& name) : name(name)
	{

	}

	Camera::~Camera()
	{
		if (renderTexture)
		{
			auto assetManager = AssetManager::GetInstance();
			assetManager->DestroyTexture(renderTexture);
		}
	}

	void Camera::Update()
	{
		EngineObject::Update();
	}

	void Camera::Draw()
	{

	}

	/////////////////////////////////////////
	Camera2D::Camera2D()
	{

	}

	Camera2D::Camera2D(const String& name) : Camera(name)
	{

	}

	Camera2D::~Camera2D()
	{

	}

	/////////////////////////////////////////
	Camera3D::Camera3D()
	{

	}

	Camera3D::Camera3D(const String& name) : Camera(name)
	{

	}

	Camera3D::~Camera3D()
	{

	}
}

