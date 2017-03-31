#include "THRenderState.h"
#include <Asset\THShader.h>
#include <Asset\THRenderTexture.h>
#include <Platform\THSurface.h>

namespace THEngine
{
	RenderState::RenderState()
	{

	}

	RenderState::~RenderState()
	{
		TH_SAFE_RELEASE(this->shader);
		TH_SAFE_RELEASE(this->renderTarget);
		TH_SAFE_RELEASE(this->depthBuffer);
	}

	void RenderState::Clear()
	{

	}
}