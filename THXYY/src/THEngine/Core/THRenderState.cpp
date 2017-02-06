#include "THRenderState.h"
#include <Asset\THShader.h>

namespace THEngine
{
	RenderState::RenderState()
	{

	}

	RenderState::~RenderState()
	{
		TH_SAFE_RELEASE(this->shader);
	}

	void RenderState::Clear()
	{
		directionalLights.Clear();
	}
}