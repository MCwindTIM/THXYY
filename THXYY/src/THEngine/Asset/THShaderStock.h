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

	private:
		ShaderStock();

	public:
		virtual ~ShaderStock();

		static ShaderStock* GetInstance();

		inline Shader* GetSkyBoxShader() const { return skyBoxShader; }
	};
}

#endif