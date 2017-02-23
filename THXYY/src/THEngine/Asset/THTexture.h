#ifndef THTEXTURE_H
#define THTEXTURE_H

#include "THAssetImpl.h"
#include "THImage.h"

namespace THEngine
{
	class TextureImpl : public AssetImpl
	{
	private:
		IDirect3DTexture9* texture = nullptr;
		Image* texImage = nullptr;
		int width, height;
		int imageWidth, imageHeight;
		float xScale, yScale;

	protected:
		TextureImpl();

	public:
		virtual ~TextureImpl();

		virtual void OnLostDevice() override;
		virtual void OnResetDevice() override;

		bool SaveToFile(const String& path);

		friend class Texture;
		friend class Application;
		friend class AssetManager;
		friend class Shader;
		friend class SpriteRenderer;
	};

	class Texture : public Object
	{
	protected:
		TextureImpl* texImpl = nullptr;

		String name;

	public:
		Texture();
		virtual ~Texture();

		inline int GetWidth() { return texImpl->width; }
		inline int GetHeight() { return texImpl->height; }
		inline int GetImageWidth() { return texImpl->imageWidth; }
		inline int GetImageHeight() { return texImpl->imageHeight; }
		inline String GetName() { return name; }

		inline bool SaveToFile(const String& path) { return texImpl->SaveToFile(path); }

		friend class Application;
		friend class AssetManager;
		friend class Shader;
		friend class SpriteRenderer;
	};
}

#endif
