#include "THRenderTexture.h"
#include <Platform\THDevice.h>

namespace THEngine
{
	void RenderTexture::OnLostDevice()
	{
	}

	void RenderTexture::OnResetDevice()
	{
		auto device = Device::GetInstance()->GetD3DDevice();

		TH_SAFE_RELEASE(this->texture);

		D3DXCreateTexture(device, width, height, 0, D3DUSAGE_AUTOGENMIPMAP | D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &this->texture);
	}
}