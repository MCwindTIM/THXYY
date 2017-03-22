#ifndef TH_SHADOW_RENDERER_H
#define TH_SHADOW_RENDERER_H

#include "THRenderer.h"
#include <Asset\THRenderTexture.h>

namespace THEngine
{
	class ShadowRenderer : public Renderer
	{
	private:
		RenderTexture* shadowMap = nullptr;
		Shader* shadowShader = nullptr;
		Light* light = nullptr;

		Matrix projPrev;
		Matrix viewPrev;
	private:
		void SetupLightProjection();

	public:
		ShadowRenderer();
		virtual ~ShadowRenderer();

		virtual void Render(GameObject* obj) override;

		inline void SetLight(Light* light) { this->light = light; }

		void Begin();
		void End();
	};
}

#endif 
