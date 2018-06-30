matrix world, projection, view;

Texture2D tex;

SamplerState TextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

struct VertexIn
{
	float3 position : POSITION;
	float4 color : COLOR0;
	float2 texCoord : TEXCOORD0;
};

struct VertexOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD0;
};

VertexOut VSFunc(VertexIn input)
{
	VertexOut output;
	matrix transform;

	transform = mul(world, view);

	output.position.xyz = input.position;
	output.position.w = 1.0f;
	output.position = mul(output.position, transform);

	output.position = mul(output.position, projection);
	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}

float4 PSFunc(VertexOut input) : SV_TARGET
{
	float4 color;
float2 uv = input.texCoord;

color = tex.Sample(TextureSampler, uv.xy);
color *= input.color;
color = saturate(color);
return color;
}

technique11 Sprite
{
	pass Pass0
	{
		SetVertexShader(CompileShader(vs_5_0, VSFunc()));
		SetPixelShader(CompileShader(ps_5_0, PSFunc()));
	}
}