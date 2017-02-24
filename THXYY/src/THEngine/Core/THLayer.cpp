#include "THLayer.h"
#include "THGame.h"

namespace THEngine
{
	Layer::Layer() : Layer(0, 0, Game::GetInstance()->GetWidth(), Game::GetInstance()->GetHeight())
	{
		
	}

	Layer::Layer(int left, int top, int width, int height)
	{
		this->left = left;
		this->top = top;
		this->width = width;
		this->height = height;

		Camera2D* camera2D = new Camera2D();
		camera2D->SetWidth(width);
		camera2D->SetHeight(height);
		camera2D->SetPosition(Vector3f(width / 2, height / 2, 0));
		camera2D->SetViewport(RectInt(0, this->width, 0, this->height));
		AddCamera(camera2D);
	}

	Layer::~Layer()
	{

	}

	void Layer::AddChild(GameObject* obj)
	{
		rootNode.AddChild(obj);
	}

	Camera* Layer::GetCameraByName(const String& name)
	{
		auto iter = cameraList.GetIterator();
		while (iter->HasNext())
		{
			auto camera = iter->Next();
			if (camera->GetName() == name)
			{
				return camera;
			}
		}
		return nullptr;
	}

	Camera* Layer::GetCameraByIndex(int index)
	{
		int i = 0;
		auto iter = cameraList.GetIterator();
		while (iter->HasNext())
		{
			auto camera = iter->Next();
			if (index == i)
			{
				return camera;
			}
			i++;
		}
		return nullptr;
	}

	Camera* Layer::GetFirstCamera()
	{
		return GetCameraByIndex(0);
	}

	void Layer::SetCameraByName(Camera* camera, const String& name)
	{
		auto iter = cameraList.GetIterator();
		while (iter->HasNext())
		{
			auto curCamera = iter->Next();
			if (curCamera->GetName() == name)
			{
				iter->Remove();
				iter->AddAfter(camera);
				return;
			}
		}
	}

	void Layer::SetCameraByIndex(Camera* camera, int index)
	{
		int i = 0;
		auto iter = cameraList.GetIterator();
		while (iter->HasNext())
		{
			iter->Next();
			if (index == i)
			{
				iter->Remove();
				iter->AddAfter(camera);
				return;
			}
			i++;
		}
	}

	void Layer::SetFirstCamera(Camera* camera)
	{
		SetCameraByIndex(camera, 0);
	}

	void Layer::Update()
	{
		EngineObject::Update();

		rootNode.Update();
	}

	void Layer::Draw()
	{
		auto iter = cameraList.GetIterator();
		while (iter->HasNext())
		{
			auto camera = iter->Next();

			DataStack::GetInstance()->Reset();
			rootNode.Visit();

			SetupRenderState();

			camera->Render(this);
		}
	}

	void Layer::SetupRenderState()
	{
		auto app = Application::GetInstance();
		auto renderState = app->GetRenderState();

		renderState->fogEnable = this->fogEnable;
		renderState->fog = this->fog;

		renderState->lightingEnable = lightingEnable;

		auto iter = lights.GetIterator();
		while (iter->HasNext())
		{
			auto light = iter->Next();
			switch (light->GetType())
			{
			case Light::DIRECTIONAL:
				renderState->directionalLights.Add((DirectionalLight*)light);
				break;
			}
		}
	}

	void Layer::DestroyObjectImmediately(GameObject* obj)
	{
		obj->OnDestroy();
		rootNode.RemoveChild(obj);
	}

	void Layer::OnDestroy()
	{
		rootNode.OnDestroy();
	}

	void Layer::Clear()
	{
		rootNode.RemoveAllChildren();
		lights.Clear();
	}
}

