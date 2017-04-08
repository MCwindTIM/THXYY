#include "lighting.fx"

#define SHADOW_EPSILON 0.0005f

struct Fog
{
	float4 color;
	float start;
	float end;
};

matrix mvMatrix, normalMatrix, projection, lightViewProjection;
texture tex;
texture shadowMap;
float4 argb;
bool fogEnable;
bool hasTexture;
int shadowMapWidth, shadowMapHeight;
Fog fog;

sampler TextureSampler = sampler_state
{ 
	texture = <tex>;
	magfilter = LINEAR;
	minfilter = LINEAR;
	mipfilter = LINEAR;
	AddressU = WRAP;
 	AddressV = WRAP;
};

sampler ShadowSampler = sampler_state
{
	texture = <shadowMap>;
	magfilter = POINT;
	minfilter = POINT;
	mipfilter = POINT;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

VertexOut VSFunc(VertexIn input)
{
	VertexOut output;

	output.sv_position.xyz = input.position;
	output.sv_position.w = 1.0f;
	output.posInShadowMap = mul(output.sv_position, lightViewProjection);
	output.sv_position = mul(output.sv_position, mvMatrix);
	
	output.positionInView = output.sv_position;
	output.sv_position = mul(output.sv_position, projection);

	output.texCoord = input.texCoord;

	float4 normal4;
	normal4.xyz = input.normal.xyz;
	normal4.w = 0;

	float4 outputNormal4 = mul(normal4, normalMatrix);

	output.normal = outputNormal4.xyz;

	return output;
}

void fogShading(inout float4 color, in PixelIn input)
{
	if (fogEnable)
	{
		float3 posInView = (input.positionInView).xyz;
		float distToCamera = length(posInView);
		float fogLerp = saturate((distToCamera - fog.start) / (fog.end - fog.start)) * fog.color.w;
		color.xyz = lerp(color.xyz, fog.color.xyz, fogLerp);
	}
}

float4 getTexturedColor(in PixelIn input)
{
	float4 color = argb;
	if (hasTexture)
	{
		color *= tex2D(TextureSampler, input.texCoord.xy);
	}
	else
	{
		color *= material.diffuse;
	}
	return color;
}

float getLightDensity(in PixelIn input)
{
	float2 shadowTex = 0.5 * input.posInShadowMap.xy / input.posInShadowMap.w + float2(0.5, 0.5);
	shadowTex.y = 1.0f - shadowTex.y;

	float depth = input.posInShadowMap.z / input.posInShadowMap.w;

	float2 texelPos;
	texelPos.x = shadowMapWidth * shadowTex.x;
	texelPos.y = shadowMapHeight * shadowTex.y;
        
	float2 lerps = frac(texelPos);
	float dx = 1.0 / shadowMapWidth;
	float dy = 1.0 / shadowMapHeight;

	float sourcevals[4];
	sourcevals[0] = (tex2D(ShadowSampler, shadowTex).r + SHADOW_EPSILON < depth) ? 0.0f : 1.0f;
	sourcevals[1] = (tex2D(ShadowSampler, shadowTex + float2(dx, 0)).r + SHADOW_EPSILON < depth) ? 0.0f : 1.0f;
	sourcevals[2] = (tex2D(ShadowSampler, shadowTex + float2(0, dy)).r + SHADOW_EPSILON < depth) ? 0.0f : 1.0f;
	sourcevals[3] = (tex2D(ShadowSampler, shadowTex + float2(dx, 1.0 / shadowMapHeight)).r + SHADOW_EPSILON < depth) ? 0.0f : 1.0f;

	float amount = lerp(lerp(sourcevals[0], sourcevals[1], lerps.x),
		lerp(sourcevals[2], sourcevals[3], lerps.x),
		lerps.y);

	return amount;
}

float4 PSFunc(PixelIn input) : COLOR
{
	float4 color;

	color = getTexturedColor(input);
	fogShading(color, input);

	return color;
}

float4 PSFunc_Ambient(PixelIn input) : COLOR
{
	float4 color;

	color = getTexturedColor(input); 
	color = ambientLighting(color);
	fogShading(color, input);

	return color;
}

float4 PSFunc_Directional(PixelIn input) : COLOR
{
	float4 color;

	color = getTexturedColor(input);
	color = shadeWithDirectional(color, input);
	color *= getLightDensity(input);
	fogShading(color, input);

	return color;
}

technique Mesh
{
	pass Pass0
	{
		VertexShader = compile vs_2_0 VSFunc();
		PixelShader = compile ps_2_0 PSFunc();
	}
}

technique Ambient
{
	pass Pass0
	{
		VertexShader = compile vs_2_0 VSFunc();
		PixelShader = compile ps_2_0 PSFunc_Ambient();
	}
}

technique Directional
{
	pass Pass0
	{
		VertexShader = compile vs_2_0 VSFunc();
		PixelShader = compile ps_3_0 PSFunc_Directional();
	}
}