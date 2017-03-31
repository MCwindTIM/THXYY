#include "THShadowRenderer.h"
#include <Platform\THApplication.h>
#include <Asset\THAssetManager.h>
#include <Core\THGame.h>

namespace THEngine
{
	ShadowRenderer::ShadowRenderer()
	{
		
	}

	ShadowRenderer::~ShadowRenderer()
	{
		TH_SAFE_RELEASE(this->shadowMap);
		TH_SAFE_RELEASE(this->depthBuffer);
	}

	ShadowRenderer* ShadowRenderer::Create()
	{
		ShadowRenderer* renderer = new ShadowRenderer();
		auto assetManager = AssetManager::GetInstance();

		renderer->shadowMap = assetManager->CreateFloatTexture(512, 512);
		if (renderer->shadowMap == nullptr)
		{
			ExceptionManager::GetInstance()->PushException(new Exception(("创建shadow map失败。")));
			delete renderer;
			return nullptr;
		}
		renderer->shadowMap->Retain();

		renderer->depthBuffer = Application::GetInstance()->CreateDepthBuffer(512, 512);
		if (renderer->depthBuffer == nullptr)
		{
			ExceptionManager::GetInstance()->PushException(new Exception(("创建shadow map深度缓存失败。")));
			delete renderer;
			return nullptr;
		}
		renderer->depthBuffer->Retain();

		renderer->shadowShader = Game::GetInstance()->GetAssetManager()->CreateShaderFromFile("fx/shadow.fx");
		if (renderer->shadowShader)
		{
			renderer->shadowShader->SetTechnique("Shadow");
		}
		else
		{
			delete renderer;
			return nullptr;
		}

		return renderer;
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
		this->projPrev = renderState->GetProjectionMatrix();
		this->viewPrev = renderState->GetViewMatrix();
		this->renderTargetPrev = renderState->GetRenderTarget();
		this->viewportPrev = renderState->GetViewport();
		this->depthTestEnabledPrev = renderState->IsDepthTestEnabled();
		this->depthBufferPrev = renderState->GetDepthBuffer();
		
		app->SetRenderTarget(shadowMap);
		app->SetDepthBuffer(depthBuffer);
		app->ClearBuffer();
		app->ClearColorBuffer(Vector4f(1, 0, 0, 1));
		app->EnableDepthTest(true);
		app->SetViewport(0, 0, shadowMap->GetWidth(), shadowMap->GetHeight());

		app->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		app->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		SetupLightProjection();

		this->shadowShader->Use();
	}

	void ShadowRenderer::End()
	{
		auto app = Application::GetInstance();

		app->SetBlendMode(ADD);

		app->SetRenderTarget(this->renderTargetPrev);
		app->SetProjectionMatrix(this->projPrev);
		app->SetViewMatrix(this->viewPrev);
		app->SetViewport(this->viewportPrev.x, this->viewportPrev.y, this->viewportPrev.width, this->viewportPrev.height);
		app->SetDepthBuffer(this->depthBufferPrev);
		app->EnableDepthTest(this->depthTestEnabledPrev);

		static int i = 1;
		if (i == 1)
		{ 
			this->shadowMap->SaveToFile("shadow.jpg");
		}
		i++;
	}
}