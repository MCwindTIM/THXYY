#ifndef TH_RENDERER_H
#define TH_RENDERER_H

#include "THRenderer.h"
#include <Platform\THApplication.h>

namespace THEngine
{
	void Renderer::SetupRenderState(GameObject* obj)
	{
		auto app = Application::GetInstance();

		app->SetBlendMode(obj->GetBlendMode());
	}
}

#endif