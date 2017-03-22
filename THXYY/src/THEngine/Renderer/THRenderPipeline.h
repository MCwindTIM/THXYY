#ifndef TH_RENDER_PIPELINE_H
#define TH_RENDER_PIPELINE_H

#include <Common\THCommon.h>
#include "THSpriteRenderer.h"
#include "THParticle3DRenderer.h"
#include "THMeshRenderer.h"
#include "THSkyBoxRenderer.h"
#include "THShadowRenderer.h"
#include "THRenderQueue.h"

namespace THEngine
{
	class RenderPipeline : public Object
	{
	private:
		SpriteRenderer* spriteRenderer = nullptr;
		Particle3DRenderer* particle3DRenderer = nullptr;
		MeshRenderer* meshRenderer = nullptr;
		SkyBoxRenderer* skyBoxRenderer = nullptr;
		ShadowRenderer* shadowRenderer = nullptr;

		SpriteRenderQueue* spriteQueue = nullptr;
		NormalRenderQueue* normalQueue = nullptr;

	private:
		RenderPipeline();

		void Render3D();
		void RenderShadowMap(Light* light);

	public:
		enum RenderQueueType
		{
			SPRITE,
			NORMAL
		};

	public:
		virtual ~RenderPipeline();

		static RenderPipeline* Create();

		void Render();

		void SendToRenderQueue(RenderQueueType type, GameObject* obj);

		inline SpriteRenderer* GetSpriteRenderer() const { return spriteRenderer; }
		inline Particle3DRenderer* GetParticle3DRenderer() const { return particle3DRenderer; }
		inline MeshRenderer* GetMeshRenderer() const { return meshRenderer; }
		inline SkyBoxRenderer* GetSkyBoxRenderer() const { return skyBoxRenderer; }
	};
}

#endif