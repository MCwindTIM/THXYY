#include "THRenderPipeline.h"
#include "THShadowRenderer.h"
#include "THSpriteRenderer.h"
#include "THParticle3DRenderer.h"
#include "THMeshRenderer.h"
#include "THSkyBoxRenderer.h"
#include "THRenderQueue.h"
#include "THTerrainRenderer.h"
#include <Core\THGame.h>
#include <Core\THGameObject.h>
#include <Core\THConfig.h>
#include <Graphic\THDevice.h>

namespace THEngine
{
	RenderPipeline::RenderPipeline()
	{
	}

	RenderPipeline::~RenderPipeline()
	{
	}

	Ptr<RenderPipeline> RenderPipeline::Create()
	{
		RenderPipeline* r = (RenderPipeline*)malloc(sizeof(RenderPipeline));
		new(r) RenderPipeline();
		Ptr<RenderPipeline> pipeline = Ptr<RenderPipeline>::Create_NoRetain(r);
		auto exceptionManager = ExceptionManager::GetInstance();

		pipeline->spriteQueue = Ptr<SpriteRenderQueue>::New();
		pipeline->normalQueue = Ptr<NormalRenderQueue>::New();
		pipeline->spriteRenderer = SpriteRenderer::Create();
		if (pipeline->spriteRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = Ptr<Exception>::New((String)"创建SpriteRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			return nullptr;
		};

		pipeline->particle3DRenderer = Particle3DRenderer::Create();
		if (pipeline->particle3DRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = Ptr<Exception>::New((String)"创建Particle3DRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			return nullptr;
		}

		pipeline->meshRenderer = MeshRenderer::Create();
		if (pipeline->meshRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = Ptr<Exception>::New((String)"创建MeshRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			return nullptr;
		}

		pipeline->skyBoxRenderer = SkyBoxRenderer::Create();
		if (pipeline->skyBoxRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = Ptr<Exception>::New((String)"创建SkyBoxRenderer失败。原因是：\n" + exception->GetInfo());
			exceptionManager->PushException(newException);
			return nullptr;
		}

		pipeline->dirShadowRenderer = DirLightShadowRenderer::Create();
		if (pipeline->dirShadowRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = Ptr<Exception>::New((String)"创建DirectionalLightShadowRenderer失败。原因是：\n"
				+ exception->GetInfo());
			exceptionManager->PushException(newException);
			return nullptr;
		}

		pipeline->terrainRenderer = TerrainRenderer::Create();
		if (pipeline->terrainRenderer == nullptr)
		{
			auto exception = exceptionManager->GetException();
			auto newException = Ptr<Exception>::New((String)"创建TerrainRenderer失败。原因是：\n"
				+ exception->GetInfo());
			exceptionManager->PushException(newException);
			return nullptr;
		}

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
		auto device = Device::GetInstance();
		auto renderState = device->GetRenderState();

		auto config = Game::GetInstance()->GetConfig();
		if (config->useLighting && renderState->IsLightingEnabled())
		{
			// render ambient light
			renderState->forwardRenderingState.isRenderingAmbient = true;
			normalQueue->Render();
			renderState->forwardRenderingState.isRenderingAmbient = false;

			// render other lights
			BlendMode prevBlendMode = renderState->GetBlendMode();
			BlendMode blendMode;
			blendMode.srcFactor = BlendFactor::SRC_ALPHA;
			blendMode.destFactor = BlendFactor::ONE;
			device->SetBlendMode(blendMode);
			auto lights = renderState->GetLights();
			auto iter = lights->GetIterator();
			while (iter->HasNext())
			{
				auto light = iter->Next();
				RenderWithLight(light);
			}

			device->SetBlendMode(prevBlendMode);
		}
		else
		{
			normalQueue->Render();
		}
		normalQueue->Clear();
	}

	void RenderPipeline::RenderShadowMap(Ptr<Light> light)
	{
		ShadowRenderer* shadowRenderer = nullptr;
		switch (light->GetType())
		{
		case Light::DIRECTIONAL:
			shadowRenderer = this->dirShadowRenderer.Get();
			this->dirShadowRenderer->SetLight((DirectionalLight*)light.Get());
			break;
		default:
			throw std::logic_error("not implemented");
		}

		shadowRenderer->RenderShadow(normalQueue.Get());
	}

	void RenderPipeline::RenderWithLight(Ptr<Light> light)
	{
		auto renderState = Device::GetInstance()->GetRenderState();
		if (renderState->GetRenderingPath() == RenderingPath::FORWARD)
			renderState->forwardRenderingState.currentLight = light;

		auto config = Game::GetInstance()->GetConfig();
		if (config->useShadow)
		{
			RenderShadowMap(light);
			renderState->forwardRenderingState.shadowMap = this->dirShadowRenderer->GetCascadedShadowMaps()->Get(0);
		}

		auto normalObjects = this->normalQueue->GetObjects();
		for (auto iter = normalObjects->GetIterator(); iter->HasNext();)
		{
			iter->Next()->Draw();
		}

		/*switch (light->GetType())
		{
		case Light::DIRECTIONAL:
			this->dirLightRenderer->SetCurrentLight(light);
			this->dirLightRenderer->SetShadowMapNear(this->dirShadowRenderer->GetCascadedShadowMaps()->Get(0));
			this->dirLightRenderer->SetShadowMapMid(this->dirShadowRenderer->GetCascadedShadowMaps()->Get(1));
			this->dirLightRenderer->SetShadowMapFar(this->dirShadowRenderer->GetCascadedShadowMaps()->Get(2));
			this->dirLightRenderer->RenderObjects((NormalRenderQueue*)normalQueue.Get());
			break;
		default:
			throw std::logic_error("not implemented");
		}*/
	}
}