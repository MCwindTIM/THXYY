#include "lighting.hlsli"

struct TerrainVertexInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct TerrainVertexOut
{
	float4 sv_position : SV_POSITION;
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

Texture2D g_heightMap;
Texture2D g_texture;

cbuffer cbPerObject
{
	float g_zscale;
	struct TerrainMaterial
	{
		float4 ambient;
		float4 diffuse;
		float4 specular;
		float4 emissive;
		float shininess;
	}g_material;
	bool g_hasTexture;
	float2 g_cellSize;
	float2 g_dTexCoord;
};

SamplerState g_heightMapSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

SamplerState g_textureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

TerrainVertexOut VS_Terrain(in TerrainVertexInput input)
{
	TerrainVertexOut output;
	output.sv_position.xyz = input.position;
	output.sv_position.y = g_heightMap.SampleLevel(g_heightMapSampler, input.uv, 0).r * g_zscale;
	output.sv_position.w = 1;

	output.sv_position = mul(output.sv_position, TH_worldMatrix);
	output.position = output.sv_position.xyz / output.sv_position.w;
	output.sv_position = mul(output.sv_position, TH_viewMatrix);
	output.sv_position = mul(output.sv_position, TH_projection);
	output.uv = input.uv;

	//compute normal
	float2 leftTex = input.uv - float2(g_dTexCoord.x, 0);
	float2 rightTex = input.uv + float2(g_dTexCoord.x, 0);
	float2 bottomTex = input.uv - float2(g_dTexCoord.y, 0);
	float2 topTex = input.uv + float2(g_dTexCoord.y, 0);
	float leftY = g_heightMap.SampleLevel(g_heightMapSampler, leftTex, 0).r * g_zscale;
	float rightY = g_heightMap.SampleLevel(g_heightMapSampler, rightTex, 0).r * g_zscale;
	float bottomY = g_heightMap.SampleLevel(g_heightMapSampler, bottomTex, 0).r * g_zscale;
	float topY = g_heightMap.SampleLevel(g_heightMapSampler, topTex, 0).r * g_zscale;

	float3 tangentX = normalize(float3(2.0f * g_cellSize.x, rightY - leftY, 0.0f));
	float3 tangentZ = normalize(float3(0.0f, topY - bottomY, 2.0f * g_cellSize.y));
	float3 normal = -cross(tangentX, tangentZ);

	float4 normal4;
	normal4.xyz = normal;
	normal4.w = 0;
	float4 outputNormal4 = mul(normal4, TH_normalMatrix);
	output.normal = outputNormal4.xyz;

	return output;
}

float4 PS_Terrain(in TerrainVertexOut input) : SV_TARGET
{
	float4 diffuse = g_hasTexture ? g_texture.Sample(g_textureSampler, input.uv) : g_material.diffuse;
	return THShade(g_material.ambient, diffuse, g_material.specular, g_material.emissive,
		g_material.shininess, input.normal, input.position);
}

technique11 Terrain
{
	pass Pass0
	{
		SetVertexShader(CompileShader(vs_5_0, VS_Terrain()));
		SetPixelShader(CompileShader(ps_5_0, PS_Terrain()));
	}
}