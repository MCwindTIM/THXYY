#ifndef TH_RENDER_TEXTURE_H
#define TH_RENDER_TEXTURE_H

#include "THTexture.h"

namespace THEngine
{
	class RenderTexture : public Texture
	{
	public:
		RenderTexture() = default;
		virtual ~RenderTexture() = default;

		virtual void OnLostDevice() override;
		virtual void OnResetDevice() override;
	};
}

#endif