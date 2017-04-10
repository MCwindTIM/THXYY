#ifndef TH_SHADER_STOCK_H
#define TH_SHADER_STOCK_H

#include "THShader.h"

namespace THEngine
{
	class ShaderStock : public Shader
	{
	private:
		static ShaderStock* instance;

		Shader* skyBoxShader = nullptr;
		Shader* shadowShader = nullptr;
		Shader* meshShader = nullptr;
		Shader* spriteShader = nullptr;

	private:
		ShaderStock();

	public:
		virtual ~ShaderStock();

		static ShaderStock* GetInstance();
		static ShaderStock* Create();

		inline Shader* GetSkyBoxShader() const { return skyBoxShader; }
		inline Shader* GetShadowShader() const { return shadowShader; }
		inline Shader* GetSpriteShader() const { return spriteShader; }
		inline Shader* GetMeshShader() const { return meshShader; }
	};
}

#endif