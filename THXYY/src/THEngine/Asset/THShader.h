#ifndef THSHADER_H
#define THSHADER_H

#include "../Common/THCommon.h"
#include "THTexture.h"
#include <Math\THMath.h>

namespace THEngine
{
	class AssetManager;

	class Shader : public Object
	{
	protected:
		ID3DXEffect* effect;
		UINT passNum;
		String path;
		int currentPass = -1;

	public:
		Shader();
		virtual ~Shader();

		inline void SetTechnique(char* technique)
		{
			effect->SetTechnique(technique);
		}

		void Use();

		void End();

		inline void CommitChanges()
		{
			this->effect->CommitChanges();
		}

		inline void UsePass(unsigned int pass) 
		{
			if (currentPass != pass)
			{
				currentPass = pass;
				effect->BeginPass(pass);
			}
		}

		inline void EndPass() 
		{ 
			currentPass = -1;
			effect->EndPass(); 
		}

		inline UINT GetPassNum() { return passNum; }

		inline void SetTexture(char* textureName, Texture* texture)
		{
			effect->SetTexture(textureName, texture->texture);
		}

		inline void SetInt(char* name, int value)
		{
			effect->SetInt(name, value);
		}

		inline void SetBoolean(char* name, bool value)
		{
			effect->SetBool(name, value);
		}

		inline void SetFloatArray(char* name, float* value, int count)
		{
			effect->SetFloatArray(name, value, count);
		}

		inline void SetMatrix(char* name, const Matrix& value)
		{
			effect->SetMatrix(name, &value.matrix);
		}

		inline void SetValue(char* name, void* value, int size)
		{
			effect->SetValue(name, value, size);
		}

		void OnLostDevice();
		void OnResetDevice();

		friend class AssetManager;
	};
}

#endif