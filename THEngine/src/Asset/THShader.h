#ifndef THSHADER_H
#define THSHADER_H

#include <unordered_map>
#include <Common\THCommon.h>
#include <Math\THMath.h>
#include <External\d3dx11effect.h>
#include <DirectXMath.h>

using namespace DirectX;

namespace THEngine
{
	class AssetManager;
	class Texture;
	class CubeMap;

	class Shader : public Object
	{
	protected:
		ID3DX11Effect * effect;
		ID3DX11EffectTechnique* currentTech = nullptr;
		ID3DX11EffectPass* currentPass = nullptr;
		UINT passNum;
		String path;
		int currentPassIndex = -1;

		// caches
		std::unordered_map<char*, ID3DX11EffectShaderResourceVariable*> shaderResCache;

	private:
		bool CompileFromFile(const String& path);

	public:
		Shader();
		virtual ~Shader();

		void SetTechnique(char* technique);

		void Use();

		void End();

		void CommitChanges();

		void UsePass(unsigned int pass);

		void EndPass();

		inline UINT GetPassNum() { return passNum; }

		void SetTexture(char* textureName, Ptr<Texture> texture);

		void SetCubeMap(char* textureName, Ptr<CubeMap> cubeMap);

		inline void SetInt(char* name, int value)
		{
			effect->GetVariableByName(name)->AsScalar()->SetInt(value);
		}

		inline void SetFloat(char* name, float value)
		{
			effect->GetVariableByName(name)->AsScalar()->SetFloat(value);
		}

		inline void SetBoolean(char* name, bool value)
		{
			effect->GetVariableByName(name)->AsScalar()->SetBool(value);
		}

		inline void SetFloat2(char* name, const Vector2f& value)
		{
			XMVECTOR v = XMVectorSet(value.x, value.y, 0, 0);
			effect->GetVariableByName(name)->AsVector()->SetFloatVector((float*)&v);
		}

		inline void SetFloat3(char* name, const Vector3f& value)
		{
			XMVECTOR v = XMVectorSet(value.x, value.y, value.z, 0);
			effect->GetVariableByName(name)->AsVector()->SetFloatVector((float*)&v);
		}

		inline void SetFloat4(char* name, const Vector4f& value)
		{
			XMVECTOR v = XMVectorSet(value.x, value.y, value.z, value.w);
			effect->GetVariableByName(name)->AsVector()->SetFloatVector((float*)&v);
		}

		inline void SetMatrix(char* name, const Matrix& value)
		{
			effect->GetVariableByName(name)->AsMatrix()->SetMatrix((float*)&value.matrix);
		}

		inline void SetValue(char* name, void* value, int size)
		{
			effect->GetVariableByName(name)->SetRawValue(value, 0, size);
		}

		void OnLostDevice();
		void OnResetDevice();

		friend class AssetManager;
		friend class Device;
	};
}

#endif