#include "THAssetManager.h"
#include "THImage.h"
#include "THRenderTexture.h"
#include "THFloatTexture.h"
#include <Core\THGame.h>
#include <Graphic\THDevice.h>
#include <External\DirectXTK\WICTextureLoader.h>

using namespace DirectX;

#ifdef _DEBUG
#pragma comment(lib, "DirectXTK/debug/DirectXTK.lib")
#else
#pragma comment(lib, "DirectXTK/release/DirectXTK.lib")
#endif

namespace THEngine
{
	bool AssetManager::Init()
	{
		return true;
	}

	Ptr<Shader> AssetManager::CreateShaderFromFile(const String& filePath)
	{
		Ptr<Shader> shader = Ptr<Shader>::New();

		if (shader->CompileFromFile(filePath) == false)
			return nullptr;

		shader->path = filePath;
		shaderList.Add(shader);
		return shader;
	}

	inline void AssetManager::DestroyShader(Ptr<Shader> shader)
	{
		shaderList.Remove(shader);
	}

	Ptr<Texture> AssetManager::CreateTextureFromFile(const String& filePath)
	{
		HRESULT hr;
		auto exceptionManager = ExceptionManager::GetInstance();
		auto texture = Ptr<Texture>::New();
		auto device = Device::GetInstance();
		auto d3dDevice = device->GetD3DDevice();
		auto context = device->GetD3D11Context();

		Ptr<Image> image = Image::Load(filePath);
		if (image == nullptr)
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				((String)"无法加载纹理:" + filePath + "。原因是:\n" + exceptionManager->GetException()->GetInfo())));
			return nullptr;
		}

		texture->imageWidth = image->GetWidth();
		texture->imageHeight = image->GetHeight();

		int texWidth, texHeight;
		texWidth = texHeight = 1;
		while (texWidth < texture->imageWidth)
		{
			texWidth *= 2;
		}
		while (texHeight < texture->imageHeight)
		{
			texHeight *= 2;
		}
		texture->width = texture->imageWidth;
		texture->height = texture->imageHeight;
		texture->xScale = (float)texture->imageWidth / texture->width;
		texture->yScale = (float)texture->imageHeight / texture->height;
		texture->name = filePath;
		texture->texImage = image;

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = texture->width;
		desc.Height = texture->height;
		desc.MipLevels = 0;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		if (FAILED(hr = d3dDevice->CreateTexture2D(&desc, nullptr, &texture->texture)))
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				((String)"无法加载纹理:" + filePath + "。原因是:\nCreateTexture2D失败。")));
			return nullptr;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = -1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		if (FAILED(hr = d3dDevice->CreateShaderResourceView(texture->texture, &srvDesc, &texture->shaderResourceView)))
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				((String)"无法加载纹理:" + filePath + "。原因是:\nCreateShaderResourceView失败。")));
			return nullptr;
		}

		texture->waitFillData = true;

		/*if (FAILED(CreateWICTextureFromFileEx(d3dDevice, context, filePath.GetBuffer(), 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, WIC_LOADER_IGNORE_SRGB,
		reinterpret_cast<ID3D11Resource**>(&texture->texture), &texture->shaderResourceView)))
		{
		exceptionManager->PushException(Ptr<Exception>::New(
		((String)"无法加载纹理:" + filePath + "。原因是:\nCreateWICTextureFromFile失败。")));
		return nullptr;
		}*/

		TH_LOCK(this->mutex)
		{
			textureList.Add(texture);
		}

		return texture;
	}

	Ptr<CubeMap> AssetManager::CreateCubeMapFromFile(const String& front, const String& back,
		const String& left, const String& right, const String& top, const String& bottom)
	{
		auto exceptionManager = ExceptionManager::GetInstance();
		auto device = Device::GetInstance()->GetD3DDevice();
		auto cubeMap = Ptr<CubeMap>::New();

		Ptr<Image> frontImage = Image::Load(front);
		Ptr<Image> backImage = Image::Load(back);
		Ptr<Image> leftImage = Image::Load(left);
		Ptr<Image> rightImage = Image::Load(right);
		Ptr<Image> topImage = Image::Load(top);
		Ptr<Image> bottomImage = Image::Load(bottom);

		if (frontImage == nullptr || backImage == nullptr || leftImage == nullptr || rightImage == nullptr
			|| topImage == nullptr || bottomImage == nullptr)
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				((String)"无法加载立方体纹理。原因是:\n" + exceptionManager->GetException()->GetInfo())));
			return nullptr;
		}

		int imgWidth = frontImage->GetWidth();
		int imgHeight = frontImage->GetHeight();
		if (imgWidth != imgHeight)
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				((String)"无法加载立方体纹理。原因是:\n纹理长宽不相等。")));
			return nullptr;
		}

		if ((backImage->GetWidth() != imgWidth) || (backImage->GetHeight() != imgHeight)
			|| (leftImage->GetWidth() != imgWidth) || (leftImage->GetHeight() != imgHeight)
			|| (rightImage->GetWidth() != imgWidth) || (rightImage->GetHeight() != imgHeight)
			|| (topImage->GetWidth() != imgWidth) || (topImage->GetHeight() != imgHeight)
			|| (bottomImage->GetWidth() != imgWidth) || (bottomImage->GetHeight() != imgHeight))
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				((String)"无法加载立方体纹理。原因是:\n各面纹理大小不一致")));
			return nullptr;
		}

		int texWidth, texHeight;
		texWidth = texHeight = 1;
		while (texWidth < imgWidth)
		{
			texWidth *= 2;
		}
		while (texHeight < imgHeight)
		{
			texHeight *= 2;
		}

		if (texWidth != imgWidth || texHeight != imgHeight)
		{
			float scaleX = (float)imgWidth / texWidth;
			float scaleY = (float)imgHeight / texHeight;
			//TODO : Scale the image.
		}

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = texWidth;
		desc.Height = texHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 6;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		D3D11_SUBRESOURCE_DATA data[6];
		for (int i = 0; i < 6; i++)
		{
			data[i].SysMemPitch = texWidth * 4;
			data[i].SysMemSlicePitch = 0;
		}
		data[0].pSysMem = leftImage->GetData();
		data[1].pSysMem = rightImage->GetData();
		data[2].pSysMem = topImage->GetData();
		data[3].pSysMem = bottomImage->GetData();
		data[4].pSysMem = frontImage->GetData();
		data[5].pSysMem = backImage->GetData();

		HRESULT hr;
		if (FAILED(hr = device->CreateTexture2D(&desc, data, &cubeMap->cubeTexture)))
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				("无法加载立方体纹理。原因是:\nCreateTexture2D失败。错误代码：" + hr)));
			return nullptr;
		}

		// cteate render target view
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.MipSlice = 0;
		rtvDesc.Texture2DArray.ArraySize = 1;
		for (int i = 0; i < 6; i++)
		{
			rtvDesc.Texture2DArray.FirstArraySlice = i;
			if (FAILED(hr = device->CreateRenderTargetView(cubeMap->cubeTexture, &rtvDesc,
				&cubeMap->renderTargetView[i])))
			{
				exceptionManager->PushException(Ptr<Exception>::New(
					("无法加载立方体纹理。原因是:\nCreateRenderTargetView失败。错误代码：" + hr)));
				return nullptr;
			}
		}

		// create shader resource view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MostDetailedMip = 0;
		srvDesc.TextureCube.MipLevels = -1;
		if (FAILED(hr = device->CreateShaderResourceView(cubeMap->cubeTexture, &srvDesc,
			&cubeMap->shaderResourceView)))
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				("无法加载立方体纹理。原因是:\nCreateShaderResourceView失败。错误代码：" + hr)));
			return nullptr;
		}

		TH_LOCK(this->mutex)
		{
			this->cubeMapList.Add(cubeMap);
		}

		return cubeMap;
	}

	Ptr<RenderTexture> AssetManager::CreateRenderTexture(int width, int height)
	{
		HRESULT hr;
		auto texture = Ptr<RenderTexture>::New();
		auto device = Device::GetInstance()->GetD3DDevice();
		auto exceptionManager = ExceptionManager::GetInstance();

		texture->width = width;
		texture->height = height;

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 0;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		if (FAILED(hr = device->CreateTexture2D(&desc, nullptr, &texture->texture)))
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				("无法创建渲染纹理。原因是:\nCreateTexture2D失败。错误代码：" + hr)));
			return nullptr;
		}
		device->CreateRenderTargetView(texture->texture, nullptr, &texture->renderTargetView);
		device->CreateShaderResourceView(texture->texture, nullptr, &texture->shaderResourceView);

		TH_LOCK(this->mutex)
		{
			textureList.Add(texture.Get());
		}

		return texture;
	}

	Ptr<FloatTexture> AssetManager::CreateFloatTexture(int width, int height)
	{
		auto texture = Ptr<FloatTexture>::New();
		auto device = Device::GetInstance()->GetD3DDevice();
		auto exceptionManager = ExceptionManager::GetInstance();;
		HRESULT hr;

		texture->width = width;
		texture->height = height;

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		if (FAILED(hr = device->CreateTexture2D(&desc, nullptr, &texture->texture)))
		{
			exceptionManager->PushException(Ptr<Exception>::New(
				("无法创建渲染纹理。原因是:\nCreateTexture2D失败。错误代码：" + hr)));
			return nullptr;
		}
		device->CreateRenderTargetView(texture->texture, nullptr, &texture->renderTargetView);
		device->CreateShaderResourceView(texture->texture, nullptr, &texture->shaderResourceView);

		return texture;
	}

	void AssetManager::OnLostDevice()
	{
		auto iter = textureList.GetIterator();
		while (iter->HasNext())
		{
			iter->Next()->OnLostDevice();
		}

		auto iter2 = shaderList.GetIterator();
		while (iter2->HasNext())
		{
			iter2->Next()->OnLostDevice();
		}
	}

	void AssetManager::OnResetDevice()
	{
		auto iter = textureList.GetIterator();
		while (iter->HasNext())
		{
			iter->Next()->OnResetDevice();
		}

		auto iter2 = shaderList.GetIterator();
		while (iter2->HasNext())
		{
			iter2->Next()->OnResetDevice();
		}
	}

	void AssetManager::Update()
	{
		for (auto iter = textureList.GetIterator(); iter->HasNext();)
		{
			auto texture = iter->Next();
			if (texture->RefCount() == 2)  // one is refered here, anothre is refered inside the list.
				iter->Remove();
			else if (texture->waitFillData)
			{
				Device::GetInstance()->GetD3D11Context()->UpdateSubresource(texture->texture, 0,
					nullptr, texture->texImage->GetData(),
					texture->texImage->GetWidth() * 4, texture->texImage->GetHeight() * 4);
				texture->GenerateMipmap();
				texture->waitFillData = false;
			}
		}

		for (auto iter = cubeMapList.GetIterator(); iter->HasNext();)
		{
			auto cubeMap = iter->Next();
			if (cubeMap->RefCount() == 2) // one is refered here, anothre is refered inside the list.
				iter->Remove();
		}
	}
}