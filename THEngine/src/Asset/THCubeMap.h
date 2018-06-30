#ifndef TH_CUBE_MAP_H
#define TH_CUBE_MAP_H

#include "THBaseAsset.h"

namespace THEngine
{
	class CubeMap : public BaseAsset
	{
	private:
		ID3D11Texture2D * cubeTexture = nullptr;
		ID3D11RenderTargetView* renderTargetView[6] = { nullptr };
		ID3D11ShaderResourceView* shaderResourceView = nullptr;

	public:
		CubeMap();
		virtual ~CubeMap();

		virtual void OnLostDevice() override;
		virtual void OnResetDevice() override;

		friend class AssetManager;
		friend class Shader;
	};
}

#endif