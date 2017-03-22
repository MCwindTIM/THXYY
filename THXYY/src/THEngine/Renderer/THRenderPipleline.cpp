#include "THRenderPipeline.h"
#include <Core/THGame.h>

namespace THEngine
{
	RenderPipeline::RenderPipeline()
	{

	}

	RenderPipeline::~RenderPipeline()
	{
		TH_SAFE_RELEASE(spriteQueue);
		TH_SAFE_RELEASE(normalQueue);
		TH_SAFE_RELEASE(spriteRenderer);
		TH_SAFE_RELEASE(particle3DRenderer);
		TH_SAFE_RELEASE(meshRenderer);
		TH_SAFE_RELEASE(skyBoxRenderer);
	}

	RenderPipeline* RenderPipeline::Create()
	{
		RenderPipeline* pipeline = new RenderPipeline();
		auto exceptionManager = ExceptionManager::GetInstance();

		pipeline->spriteQueue = new SpriteRenderQueue();
		pipeline->spriteQueue->Retain();

		pipeline->normalQueue = new NormalRenderQueue();
		pipeline->normalQueue->Retain();

		pipeline->spriteRenderer = SpriteRenderer::Create();
		if (pipeline->spriteRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = new Exception((String)"创建SpriteRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			delete pipeline;
			return nullptr;
		}
		pipeline->spriteRenderer->Retain();

		pipeline->particle3DRenderer = Particle3DRenderer::Create();
		if (pipeline->particle3DRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = new Exception((String)"创建Particle3DRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			delete pipeline;
			return nullptr;
		}
		pipeline->particle3DRenderer->Retain();


		pipeline->meshRenderer = MeshRenderer::Create();
		if (pipeline->meshRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = new Exception((String)"创建MeshRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			delete pipeline;
			return nullptr;
		}
		pipeline->meshRenderer->Retain();

		pipeline->skyBoxRenderer = SkyBoxRenderer::Create();
		if (pipeline->skyBoxRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = new Exception((String)"创建SkyBoxRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			delete pipeline;
			return nullptr;
		}
		pipeline->skyBoxRenderer->Retain();

		return pipeline;
	}

	void RenderPipeline::Render()
	{
		spriteQueue->Render();
		spriteQueue->Clear();

		Render3D();
	}

	void RenderPipeline::SendToRenderQueue(RenderQueueType type, GameObject* obj)
	{
		switch (type)
		{
		case SPRITE:
			spriteQueue->Add(obj);
			break;
		case NORMAL:
			normalQueue->Add(obj);
			break;
		default:
			throw std::runtime_error("not implemented.");
		}
	}

	void RenderPipeline::Render3D()
	{
		auto app = Application::GetInstance();
		auto renderState = app->GetRenderState();

		if (renderState->IsLightingEnabled())
		{
			this->meshRenderer->SetRenderAmbient(true);
			normalQueue->Render();
			this->meshRenderer->SetRenderAmbient(false);

			app->SetBlendMode(BlendMode::ADD);
			auto lights = renderState->GetLights();
			auto iter = lights->GetIterator();
			while (iter->HasNext())
			{
				auto light = iter->Next();
				RenderShadowMap(light);

				this->meshRenderer->SetCurrentLight(light);
				normalQueue->Render();	
			}
			app->SetBlendMode(BlendMode::ALPHA_BLEND);
		}
		else
		{
			normalQueue->Render();
		}
		normalQueue->Clear();
	}

	void RenderPipeline::RenderShadowMap(Light* light)
	{

	}
}