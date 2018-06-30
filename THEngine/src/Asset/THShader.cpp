#include "THShader.h"
#include "THTexture.h"
#include "THCubeMap.h"
#include <Graphic\THDevice.h>
#include <d3dcompiler.h>

#ifdef _DEBUG
#pragma comment(lib, "FX11/Effects11d.lib")
#else
#pragma comment(lib, "FX11/Effects11.lib")
#endif

namespace THEngine
{
	Shader::Shader()
	{
		effect = nullptr;
	}

	Shader::~Shader()
	{
		TH_SAFE_RELEASE(currentPass);
		TH_SAFE_RELEASE(currentTech);
		TH_SAFE_RELEASE(effect);
	}

	bool Shader::CompileFromFile(const String& path)
	{
		auto device = Device::GetInstance()->GetD3DDevice();
		ID3DBlob *error = nullptr;
		HRESULT hr;
#ifdef _DEBUG
		UINT flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT flag = D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
		if (FAILED(hr = D3DX11CompileEffectFromFile(path.GetBuffer(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			flag, 0, device, &this->effect, &error)))
		{
			if (error)
			{
				String message((char*)error->GetBufferPointer());
				THMessageBox(message);
			}
			else
			{
				THMessageBox((String)"无法打开文件:" + path);
			}
			return false;
		}
		return true;
	}

	void Shader::OnLostDevice()
	{
		TH_SAFE_RELEASE(effect);
	}

	void Shader::OnResetDevice()
	{
		CompileFromFile(this->path);
	}

	void Shader::SetTexture(char* textureName, Ptr<Texture> texture)
	{
		auto device = Device::GetInstance();
		if (device->GetRenderState()->isRenderTargetDirty)
			device->SetupRenderState();

		ID3DX11EffectShaderResourceVariable* textureVar = nullptr;
		auto pos = this->shaderResCache.find(textureName);
		if (pos != this->shaderResCache.end())
		{
			textureVar = pos->second;
		}
		else
		{
			textureVar = effect->GetVariableByName(textureName)->AsShaderResource();
			this->shaderResCache[textureName] = textureVar;
		}

		textureVar->SetResource(texture->shaderResourceView);
	}

	void Shader::SetCubeMap(char* textureName, Ptr<CubeMap> cubeMap)
	{
		effect->GetVariableByName(textureName)->AsShaderResource()->SetResource(cubeMap->shaderResourceView);
	}

	void Shader::SetTechnique(char* technique)
	{
		auto renderState = Device::GetInstance()->GetRenderState();
		if (renderState->shader == this)
		{
			End();
			TH_SAFE_RELEASE(currentTech);
			currentTech = effect->GetTechniqueByName(technique);
			Use();
		}
		else
		{
			TH_SAFE_RELEASE(currentTech);
			currentTech = effect->GetTechniqueByName(technique);
		}
	}

	void Shader::Use()
	{
		auto renderState = Device::GetInstance()->GetRenderState();
		if (renderState->shader != this)
		{
			if (renderState->shader != nullptr)
			{
				renderState->shader->End();
			}
			renderState->shader = this;

			D3DX11_TECHNIQUE_DESC desc;
			currentTech->GetDesc(&desc);
			this->passNum = desc.Passes;
			this->currentPassIndex = -1;
		}
	}

	void Shader::End()
	{
		auto renderState = Device::GetInstance()->GetRenderState();
		if (renderState->shader == this)
		{
			if (this->currentPassIndex >= 0)
			{
				EndPass();
			}
			renderState->shader = nullptr;

			// clear textures
			for (auto iter = this->shaderResCache.begin();
				iter != this->shaderResCache.end(); ++iter)
			{
				iter->second->SetResource(nullptr);
			}
		}
	}

	void Shader::UsePass(unsigned int pass)
	{
		if (currentPassIndex != pass)
		{
			EndPass();
			currentPassIndex = pass;
			TH_SAFE_RELEASE(currentPass);
			currentPass = currentTech->GetPassByIndex(pass);
			currentPass->Apply(0, Device::GetInstance()->GetD3D11Context());
		}
	}

	void Shader::EndPass()
	{
		if (currentPassIndex != -1)
		{
			currentPassIndex = -1;
			TH_SAFE_RELEASE(currentPass);
		}
	}

	void Shader::CommitChanges()
	{
		if (currentPass)
			currentPass->Apply(0, Device::GetInstance()->GetD3D11Context());
	}
}