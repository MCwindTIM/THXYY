matrix mvMatrix, projection;

struct VertexOut
{
	float4 position : SV_POSITION;
};

VertexOut VSFunc(float3 input : POSITION)
{
	VertexOut output;

	output.position.xyz = input;
	output.position.w = 1.0f;
	output.position = mul(output.position, mvMatrix);
	output.position = mul(output.position, projection);

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