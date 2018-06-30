float fov;
float3 lookAt;
float3 up;
int viewportWidth;
int viewportHeight;
TextureCube skyBox;
matrix world, projection, view;

SamplerState SkyBoxSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = mirror;
	AddressV = mirror;
};

struct VertexIn
{
	float3 position : POSITION;
};

struct VertexOut
{
	float4 sv_position : SV_POSITION;
	float3 position : TEXCOORD0;
};

struct PixelIn
{
	float4 sv_position : SV_POSITION;
	float3 position : TEXCOORD0;
};

VertexOut VSFunc(VertexIn input)
{
	VertexOut output;
	matrix transform;

	transform = mul(world, view);

	output.sv_position.xyz = input.position;
	output.sv_position.w = 1.0f;
	output.sv_position = mul(output.sv_position, transform);

	output.sv_position = mul(output.sv_position, projection);
	output.position = output.sv_position.xyz;
	return output;
}

float4 PSFunc(PixelIn input) : SV_TARGET
{
	float3 front = normalize(lookAt);
	float3 up_new = normalize(up);
	float3 right = -cross(front, up_new);

	float sx = input.position.x;
	float sy = input.position.y;
	float fovScale = tan(fov * 0.5 * 3.14159 / 180);

	float3 r = right * (sx * fovScale) * viewportWidth / viewportHeight;
	float3 u = up_new * (sy * fovScale);

	float3 output_dir = normalize(r + u + front);

	//float4 test;
	//test.xyz = output_dir.xyz;
	//test.w = 1;
	//return test;
	return skyBox.Sample(SkyBoxSampler, output_dir);
}

technique11 SkyBox
{
	pass Pass0
	{
		SetVertexShader(CompileShader(vs_5_0, VSFunc()));
		SetPixelShader(CompileShader(ps_5_0, PSFunc()));
	}
}