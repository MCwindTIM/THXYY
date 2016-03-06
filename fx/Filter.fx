Texture tex;

sampler TextureSampler = sampler_state
{ 
	texture = <tex>;
	magfilter = LINEAR; 
	minfilter = LINEAR; 
	mipfilter = LINEAR;
	AddressU = mirror;
 	AddressV = mirror;
};

struct VertexOut
{
	float2 textureCoordinates : TEXCOORD0;
};

float4 PixelShaderFunction(VertexOut input) : COLOR0
{
	float4 Color;
	Color = tex2D(TextureSampler, input.textureCoordinates.xy);
	return Color;
}

technique Filter
{
	pass Pass0
	{
		PixelShader = compile ps_2_0 PixelShaderFunction();
	}
}