struct PointLight
{
	float3 position;
	float4 ambient;
	float4 diffuse;
	float4 specular;
};

struct Fog
{
	float4 color;
	float start;
	float end;
};

matrix mvMatrix, normalMatrix, projection, invProjection;
texture tex;
float4 argb;
bool fogEnable;
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

struct VertexIn
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

struct VertexOut
{
    float4 sv_position : POSITION;
	float4 position : TEXCOORD2;
	float3 normal : TEXCOORD1;
	float2 texCoord : TEXCOORD0;
};

VertexOut VSFunc(VertexIn input)
{
	VertexOut output;

	output.position.xyz = input.position;
	output.position.w = 1.0f;
	output.position = mul(output.position, mvMatrix);

	output.position = mul(output.position, projection);
	output.sv_position = output.position;

	output.texCoord = input.texCoord;

	float4 normal4;
	normal4.xyz = input.normal.xyz;
	normal4.w = 0;

	float4 outputNormal4 = mul(normal4, normalMatrix);
	outputNormal4 = mul(outputNormal4, projection);

	output.normal = outputNormal4.xyz;

	return output;
}

float4 PSFunc(VertexOut input) : COLOR
{
	float4 color;
	float2 uv = input.texCoord;

	color = tex2D(TextureSampler, uv.xy);
	color.xyz *= argb.yzw;
	color.w *= argb.x;

	if (fogEnable)
	{
		float3 posInView = (mul(input.position, invProjection)).xyz;
		float distToCamera = length(posInView);
		float fogLerp = saturate((distToCamera - fog.start) / (fog.end - fog.start));
		color = lerp(color, fog.color, fogLerp);
	}

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