#ifndef THTEXTURE_H
#define THTEXTURE_H

#include "../Common/THCommon.h"
#include "THImage.h"

namespace THEngine
{
	class Texture : public Object
	{
	protected:
		IDirect3DTexture9* texture;
		int width, height;
		int imageWidth, imageHeight;
		float xScale, yScale;

	public:
		Texture();
		virtual ~Texture();

		inline int GetWidth() { return width; }
		inline int GetHeight() { return height; }
		inline int GetImageWidth() { return imageWidth; }
		inline int GetImageHeight() { return imageHeight; }

		int SaveToFile(String path);

		friend class AssetManager;
		friend class Shader;
		friend class SpriteRenderer;
	};
}

#endif
