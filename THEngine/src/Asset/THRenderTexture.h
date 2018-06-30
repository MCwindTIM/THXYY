#ifndef TH_RENDER_TEXTURE_H
#define TH_RENDER_TEXTURE_H

#include "THTexture.h"

namespace THEngine
{
	class RenderTexture : public Texture
	{
	private:
		ID3D11RenderTargetView * renderTargetView = nullptr;

	public:
		RenderTexture() = default;
		virtual ~RenderTexture() { TH_SAFE_RELEASE(renderTargetView); }

		friend class Device;
		friend class AssetManager;
	};
}

#endif