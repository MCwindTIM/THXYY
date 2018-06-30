#ifndef TH_FORWARD_RENDERING_STATE_H
#define TH_FORWARD_RENDERING_STATE_H

#include <Common\THCommon.h>
#include <Common\THPtr.h>

namespace THEngine
{
	class Light;
	class ShadowMap;

	class ForwardRenderingState : public Object
	{
	private:
		Ptr<Light> currentLight;
		Ptr<ShadowMap> shadowMap;
		bool isRenderingAmbient = false;

	public:
		Ptr<Light> GetCurrentLight() const { return this->currentLight; }
		Ptr<ShadowMap> GetShadowMap() const { return this->shadowMap; }

		bool IsRenderingAmbient() const { return this->isRenderingAmbient; }

		friend class RenderPipeline;
	};
}

#endif
