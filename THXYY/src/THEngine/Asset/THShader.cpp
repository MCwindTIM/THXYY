#include "THShader.h"

using namespace THEngine;

Shader::Shader()
{
	effect = nullptr;
}

Shader::~Shader()
{
	TH_SAFE_RELEASE(effect);
}