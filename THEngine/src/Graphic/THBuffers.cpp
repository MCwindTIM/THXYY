#include "THBuffers.h"
#include "THDevice.h"

namespace THEngine
{
	DepthBuffer::~DepthBuffer()
	{
		TH_SAFE_RELEASE(this->buffer);
		TH_SAFE_RELEASE(this->view);
	}

	/*bool DepthBuffer::SaveToFile(const String& path)
	{
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
			THMessageBox((String)"无法将surface存储为文件。不支持的文件格式：" + ext);
			return false;
		}

		if (FAILED(D3DXSaveSurfaceToFile(path.GetBuffer(), format, surface, nullptr, nullptr)))
		{
			return false;
		}
		return true;
	}*/

	///////////////////////////////////////

	VertexBuffer::~VertexBuffer()
	{
		TH_SAFE_RELEASE(this->buffer);
	}

	///////////////////////////////////////

	void* DynamicVertexBuffer::Lock()
	{
		auto context = Device::GetInstance()->GetD3D11Context();

		D3D11_MAPPED_SUBRESOURCE resource;
		if (FAILED(context->Map(this->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
			return nullptr;
		return resource.pData;
	}

	void DynamicVertexBuffer::UnLock()
	{
		auto context = Device::GetInstance()->GetD3D11Context();
		context->Unmap(this->buffer, 0);
	}

	///////////////////////////////////////

	IndexBuffer::~IndexBuffer()
	{
		TH_SAFE_RELEASE(this->buffer);
	}

	///////////////////////////////////////

	void* DynamicIndexBuffer::Lock()
	{
		auto context = Device::GetInstance()->GetD3D11Context();

		D3D11_MAPPED_SUBRESOURCE resource;
		if (FAILED(context->Map(this->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
			return nullptr;
		return resource.pData;
	}

	void DynamicIndexBuffer::UnLock()
	{
		auto context = Device::GetInstance()->GetD3D11Context();
		context->Unmap(this->buffer, 0);
	}
}