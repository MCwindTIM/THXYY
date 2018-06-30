#include <wincodec.h>
#include "THTexture.h"
#include "THAssetManager.h"
#include "THImage.h"
#include <Graphic\THDevice.h>
#include <External\DirectXTK\ScreenGrab.h>

using namespace DirectX;

#ifdef _DEBUG
#pragma comment(lib, "DirectXTK/debug/DirectXTK.lib")
#else
#pragma comment(lib, "DirectXTK/release/DirectXTK.lib")
#endif

namespace THEngine
{
	Texture::Texture()
	{
	}

	Texture::~Texture()
	{
#ifdef _DEBUG
		THLog((String)"释放" + this->name);
#endif
		TH_SAFE_RELEASE(texture);
		TH_SAFE_RELEASE(shaderResourceView);
	}

	bool Texture::SaveToFile(const String& path)
	{
		auto device = Device::GetInstance();
		auto context = device->GetD3D11Context();

		GUID format;
		String ext = path.SubString(path.LastIndexOf(TCHAR('.')) + 1, path.GetLength());
		if (ext == "png")
		{
			format = GUID_ContainerFormatPng;
		}
		else if (ext == "jpg")
		{
			format = GUID_ContainerFormatJpeg;
		}
		else if (ext == "bmp")
		{
			format = GUID_ContainerFormatBmp;
		}
		else
		{
			THMessageBox((String)"无法将纹理存储为文件。不支持的文件格式：" + ext);
			return false;
		}

		SaveWICTextureToFile(context, this->texture, format, path.GetBuffer());
		return true;
	}

	void Texture::OnLostDevice()
	{
		/*texImage = Ptr<Image>::New(width, height);

		D3DLOCKED_RECT rect;
		texture->LockRect(0, &rect, nullptr, 0);

		unsigned char* src = (unsigned char*)rect.pBits;
		unsigned char* dest = (unsigned char*)texImage->GetData();
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				dest[j * 4] = src[j * 4 + 2];
				dest[j * 4 + 1] = src[j * 4 + 1];
				dest[j * 4 + 2] = src[j * 4];
				dest[j * 4 + 3] = src[j * 4 + 3];
			}
			dest += width * 4;
			src += rect.Pitch;
		}

		texture->UnlockRect(0);
		TH_SAFE_RELEASE(texture);*/
	}

	void Texture::OnResetDevice()
	{
		/*auto device = Device::GetInstance()->GetD3DDevice();

		if (FAILED(D3DXCreateTexture(device, width, height, 0, D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture)))
		{
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(
				((String)"纹理加载失败。原因是：\nD3DXCreateTexture失败。")));
			return;
		}

		D3DLOCKED_RECT rect;
		texture->LockRect(0, &rect, nullptr, 0);

		unsigned char* dest = (unsigned char*)rect.pBits;
		unsigned char* src = (unsigned char*)texImage->GetData();
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				dest[j * 4] = src[j * 4 + 2];
				dest[j * 4 + 1] = src[j * 4 + 1];
				dest[j * 4 + 2] = src[j * 4];
				dest[j * 4 + 3] = src[j * 4 + 3];
			}
			dest += rect.Pitch;
			src += width * 4;
		}

		texture->UnlockRect(0);*/
	}

	void Texture::GenerateMipmap()
	{
		Device::GetInstance()->GetD3D11Context()->GenerateMips(this->shaderResourceView);
	}
}