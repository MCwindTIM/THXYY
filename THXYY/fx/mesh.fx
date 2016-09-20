matrix mvMatrix, normalMatrix, projection;
texture tex;
float4 argb;

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
    float4 position : POSITION;
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