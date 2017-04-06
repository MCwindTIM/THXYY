#ifndef TH_SHADOW_RENDERER_H
#define TH_SHADOW_RENDERER_H

#include "THRenderer.h"
#include <Asset\THFloatTexture.h>
#include <Platform\THSurface.h>

namespace THEngine
{
	class ShadowRenderer : public Renderer
	{
	private:
		FloatTexture* shadowMap = nullptr;
		Surface* depthBuffer = nullptr;
		Shader* shadowShader = nullptr;
		Light* light = nullptr;
		bool depthTestEnabledPrev = true;
		Matrix lightProjection;
		Matrix lightView;

		Matrix projPrev;
		Matrix viewPrev;
		RenderTexture* renderTargetPrev = nullptr;
		Viewport viewportPrev;
		Surface* depthBufferPrev = nullptr;

	private:
		ShadowRenderer();
		void SetupLightProjection();
		void ComputeFrustum();

	public:
		virtual ~ShadowRenderer();

		static ShadowRenderer* Create();

		virtual void Render(GameObject* obj) override;

		inline void SetLight(Light* light) { this->light = light; }

		inline FloatTexture* GetShadowMap() const { return this->shadowMap; }

		inline const Matrix& GetLightProjection() const { return this->lightProjection; }

		inline const Matrix& GetLightView() const { return this->lightView; }

		void Begin();
		void End();
	};
}

#endif 
