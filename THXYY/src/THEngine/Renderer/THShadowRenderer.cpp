#include "THShadowRenderer.h"
#include <Platform\THApplication.h>
#include <Asset\THAssetManager.h>

namespace THEngine
{
	ShadowRenderer::ShadowRenderer()
	{
		auto assetManager = AssetManager::GetInstance();
		this->shadowMap = assetManager->CreateRenderTexture(512, 512);
		this->shadowMap->Retain();
	}

	ShadowRenderer::~ShadowRenderer()
	{
		TH_SAFE_RELEASE(this->shadowMap);
	}

	void ShadowRenderer::Render(GameObject* obj)
	{
		auto app = Application::GetInstance();
		auto renderState = app->GetRenderState();
	
		SetupWorldTransform(obj);

		Matrix mvMatrix = renderState->GetWorldMatrix() * renderState->GetViewMatrix();

		this->shadowShader->SetMatrix("mvMatrix", mvMatrix);
		this->shadowShader->SetMatrix("projection", renderState->GetProjectionMatrix());
		this->shadowShader->CommitChanges();

		this->shadowShader->UsePass(0);
		obj->DrawGeometry();
	}

	void ShadowRenderer::SetupLightProjection()
	{
		auto app = Application::GetInstance();
		Matrix projection;
		Matrix view;
		switch (light->GetType())
		{
		case Light::DIRECTIONAL:
			Matrix::Ortho(&projection, 0, shadowMap->GetWidth(), 0, shadowMap->GetHeight(), 0, TH_MAX_Z);
			app->SetProjectionMatrix(projection);
			Matrix::Identity(&view);
			app->SetViewMatrix(view);
			break;
		default:
			throw std::runtime_error("Not implemented.");
		}
	}

	void ShadowRenderer::Begin()
	{
		auto app = Application::GetInstance();
		auto renderState = app->GetRenderState();

		//store the  matrices
		this->projPrev = renderState->GetWorldMatrix();
		this->viewPrev = renderState->GetViewMatrix();

		SetupLightProjection();

		app->SetRenderTarget(shadowMap);

		this->shadowShader->Use();
	}

	void ShadowRenderer::End()
	{
		auto app = Application::GetInstance();

		app->SetProjectionMatrix(this->projPrev);
		app->SetViewMatrix(this->viewPrev);
	}
}