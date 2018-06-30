#include "lighting.hlsli"

struct VertexIn
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

struct VertexOut
{
	float4 sv_position : SV_POSITION;
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

cbuffer cbPerObject
{
	bool g_hasTexture;
	struct Material
	{
		float4 ambient;
		float4 diffuse;
		float4 specular;
		float4 emissive;
		float shininess;
	}g_material;
};

Texture2D g_texture;

sampler g_textureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

VertexOut VSFunc(VertexIn input)
{
	VertexOut output;

	output.sv_position.xyz = input.position;
	output.sv_position.w = 1.0f;
	output.position = mul(output.sv_position, TH_worldMatrix);
	output.sv_position = mul(output.position, TH_viewMatrix);
	output.sv_position = mul(output.sv_position, TH_projection);

	output.texCoord = input.texCoord;

	float4 normal4;
	normal4.xyz = input.normal.xyz;
	normal4.w = 0;

	float4 outputNormal4 = mul(normal4, TH_normalMatrix);

	output.normal = outputNormal4.xyz;

	return output;
}

float4 PSFunc(VertexOut input) : SV_TARGET
{
	float4 diffuse = g_hasTexture ? g_texture.Sample(g_textureSampler, input.texCoord) : g_material.diffuse;
	return THShade(g_material.ambient, diffuse, g_material.specular, g_material.emissive,
		g_material.shininess, input.normal, input.position.xyz / input.position.w);
}

technique11 Mesh
{
	pass Pass0
	{
		SetVertexShader(CompileShader(vs_5_0, VSFunc()));
		SetPixelShader(CompileShader(ps_5_0, PSFunc()));
	}
}