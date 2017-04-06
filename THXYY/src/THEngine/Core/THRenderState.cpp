#include "THRenderState.h"
#include <Asset\THShader.h>
#include <Asset\THRenderTexture.h>
#include <Platform\THSurface.h>
#include <Core\THCamera.h>

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
		TH_SAFE_RELEASE(this->camera);
	}

	void RenderState::Clear()
	{

	}
}