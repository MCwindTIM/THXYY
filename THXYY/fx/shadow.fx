matrix mvMatrix, projection;

struct VertexOut
{
	float4 position : POSITION;
	float2 depth : TEXCOORD0;
};

VertexOut VSFunc(float3 input : POSITION)
{
	VertexOut output;

	output.position.xyz = input;
	output.position.w = 1.0f;
	output.position = mul(output.position, mvMatrix);
	output.position = mul(output.position, projection);
	output.depth = output.position.zw;

	return output;
}

float PSFunc(float2 depth : TEXCOORD) : COLOR
{
	return depth.x / depth.y;
}