#ifndef THRENDERER_H
#define THRENDERER_H

#include "../Common/THCommon.h"
#include "THRenderQueue.h"
#include "../Asset/THShader.h"


namespace THEngine
{
	class Renderer : public Object
	{
	protected:
		IDirect3DDevice9* device;

	public:
		virtual void Render(GameObject* obj) = 0;
	};
}

#endif