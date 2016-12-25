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

		Image* texImage = nullptr;

		String name;

	public:
		Texture();
		virtual ~Texture();

		inline int GetWidth() { return width; }
		inline int GetHeight() { return height; }
		inline int GetImageWidth() { return imageWidth; }
		inline int GetImageHeight() { return imageHeight; }
		inline String GetName() { return name; }

		bool SaveToFile(String path);

		void OnLostDevice();
		void OnResetDevice();

		friend class Application;
		friend class AssetManager;
		friend class Shader;
		friend class SpriteRenderer;
	};
}

#endif
