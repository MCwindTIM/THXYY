Texture tex;
float4 argb;
int texWidth;
int texHeight;

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
	float2 textureCoordinates : TEXCOORD;
};

float4 PixelShaderFunction(VertexOut input) : COLOR
{
	float4 color;
	float2 uv = input.textureCoordinates;
	uv.x += 0.5 / texWidth;
	uv.y += 0.5 / texHeight;

	color = tex2D(TextureSampler, uv.xy);
	color.xyz *= argb.yzw;
	color.w *= argb.x;
	return color;
}

technique Sprite
{
	pass Pass0
	{
		PixelShader = compile ps_2_0 PixelShaderFunction();
	}
}