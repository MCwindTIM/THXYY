#ifndef TH_CUBE_MAP_H
#define TH_CUBE_MAP_H

#include "THAssetImpl.h"

namespace THEngine
{
	class CubeMapImpl : public AssetImpl
	{
	private:
		IDirect3DCubeTexture9* cubeTexture = nullptr;

	protected:
		CubeMapImpl();

	public:
		virtual ~CubeMapImpl();

		virtual void OnLostDevice() override;
		virtual void OnResetDevice() override;

		friend class AssetManager;
	};

	class CubeMap : public Object
	{
	private:
		CubeMapImpl* impl = nullptr;

	public:
		CubeMap();
		virtual ~CubeMap();

		friend class AssetManager;
	};
}

#endif