#include "THCamera.h"
#include "THLayer.h"
#include "THGame.h"
#include <Asset\THAssetManager.h>
#include <Asset\THCubeMap.h>
#include <Platform\THApplication.h>

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
		TH_SAFE_RELEASE(renderTexture);
	}

	void Camera::Update()
	{
		EngineObject::Update();
	}

	void Camera::Draw()
	{

	}

	void Camera::SetupViewport(Layer* layer)
	{
		auto app = Application::GetInstance();
		if (this->viewport.left == 0 && this->viewport.right == 0 && this->viewport.top == 0 && this->viewport.bottom == 0)
		{
			app->SetViewport(layer->GetLeft(), layer->GetTop(), layer->GetWidth(), layer->GetHeight());
		}
		else
		{
			app->SetViewport(layer->GetLeft() + this->viewport.left, layer->GetTop() + this->viewport.top,
				this->viewport.Width(), this->viewport.Height());
		}
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

	void Camera2D::Render(Layer* layer)
	{
		auto app = Application::GetInstance();

		SetupViewport(layer);

		Vector3f pos = GetPosition();
		app->SetOrtho(pos.x - GetWidth() / 2, pos.y - GetHeight() / 2, 
			GetWidth(), GetHeight(), 0, TH_MAX_Z);

		Matrix matrix;
		Matrix::Identity(&matrix);
		app->SetViewMatrix(matrix);

		Game::GetInstance()->Render();

		Application::GetInstance()->ClearDepthBuffer();
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

	void Camera3D::Render(Layer* layer)
	{
		auto app = Application::GetInstance();

		SetupViewport(layer);

		if (layer->GetSkyBox())
		{
			Game::GetInstance()->GetSkyBoxRenderer()->RenderSkyBox(this, layer);
		}

		Matrix matrix;
		if (this->viewport.left == 0 && this->viewport.right == 0 && this->viewport.top == 0 && this->viewport.bottom == 0)
		{
			Matrix::Perspective(&matrix, this->fov, (float)layer->GetWidth () / layer->GetHeight(), 0.1f, 10000.0f);
		}
		else
		{
			Matrix::Perspective(&matrix, this->fov, (float)this->viewport.Width() / this->viewport.Height(), 0.1f, 10000.0f);
		}
		app->SetProjectionMatrix(matrix);

		Matrix::LookAt(&matrix, Vector3f(this->position.x, this->position.y,  this->position.z),
			Vector3f(this->lookAt.x, this->lookAt.y, this->lookAt.z),
			Vector3f(this->up.x, this->up.y, this->up.z));
		app->SetViewMatrix(matrix);

		Game::GetInstance()->Render();

		Application::GetInstance()->ClearDepthBuffer();
	}
}

