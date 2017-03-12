#include "lighting.fx"

struct Fog
{
	float4 color;
	float start;
	float end;
};

matrix mvMatrix, normalMatrix, projection;
texture tex;
float4 argb;
bool fogEnable;
bool hasTexture;
Fog fog;

sampler TextureSampler = sampler_state
{ 
	texture = <tex>;
	magfilter = LINEAR;
	minfilter = LINEAR;
	mipfilter = LINEAR;
	AddressU = mirror;
 	AddressV = mirror;
};


VertexOut VSFunc(VertexIn input)
{
	VertexOut output;

	output.sv_position.xyz = input.position;
	output.sv_position.w = 1.0f;
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
	return color;
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
		PixelShader = compile ps_2_0 PSFunc_Directional();
	}
}