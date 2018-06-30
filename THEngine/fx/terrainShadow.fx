matrix g_mvMatrix, g_projection;
float g_zscale;
Texture2D g_heightMap;

SamplerState g_heightMapSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

struct VertexIn
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct VertexOut
{
	float4 position : SV_POSITION;
};

VertexOut VSFunc(VertexIn input)
{
	VertexOut output;

	output.position.xyz = input.position;
	output.position.y = g_heightMap.SampleLevel(g_heightMapSampler, input.uv, 0).r * g_zscale;
	output.position.w = 1.0f;
	output.position = mul(output.position, g_mvMatrix);
	output.position = mul(output.position, g_projection);

	return output;
}

float4 PSFunc(float4 position : SV_POSITION) : SV_TARGET
{
	float4 output;
	output.x = position.z / position.w;
	output.y = output.x * output.x;
	output.z = output.w = 1.0f;
	return output;
}

technique11 Shadow
{
	pass Pass0
	{
		SetVertexShader(CompileShader(vs_5_0, VSFunc()));
		SetPixelShader(CompileShader(ps_5_0, PSFunc()));
	}
}