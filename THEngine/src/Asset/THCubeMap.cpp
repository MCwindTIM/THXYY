#include "THCubeMap.h"
#include "THAssetManager.h"

namespace THEngine
{
	CubeMap::CubeMap()
	{
	}

	CubeMap::~CubeMap()
	{
		TH_SAFE_RELEASE(cubeTexture);
		for (int i = 0; i < 6; i++)
		{
			TH_SAFE_RELEASE(renderTargetView[i]);
		}
		TH_SAFE_RELEASE(shaderResourceView);
	}

	void CubeMap::OnLostDevice()
	{
	}

	void CubeMap::OnResetDevice()
	{
	}
}