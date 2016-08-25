#include "THTexture.h"

using namespace THEngine;

Texture::Texture()
{
	texture = nullptr;
}

Texture::~Texture()
{
	TH_SAFE_RELEASE(texture);
}

int Texture::SaveToFile(String path)
{
	IDirect3DSurface9* surface;
	texture->GetSurfaceLevel(0, &surface);

	D3DXIMAGE_FILEFORMAT format;
	String ext = path.SubString(path.LastIndexOf(TCHAR('.')) + 1, path.GetLength());
	if (ext == "png")
	{
		format = D3DXIFF_PNG;
	}
	else if (ext == "jpg")
	{
		format = D3DXIFF_JPG;
	}
	else if (ext == "bmp")
	{
		format = D3DXIFF_BMP;
	}
	else
	{
		THMessageBox((String)"无法将纹理存储为文件。不支持的文件格式：" + ext);
		return -1;
	}

	D3DXSaveSurfaceToFile(path.GetBuffer(), format, surface, nullptr, nullptr);
	return TH_SUCCESS;
}