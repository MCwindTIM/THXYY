#include "THShaderStock.h"

namespace THEngine
{
	ShaderStock* ShaderStock::instance = nullptr;

	ShaderStock::ShaderStock()
	{

	}

	ShaderStock::~ShaderStock()
	{

	}
	
	ShaderStock* ShaderStock::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ShaderStock();
		}
		return instance;
	}
}