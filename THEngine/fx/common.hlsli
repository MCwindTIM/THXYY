#ifndef TH_COMMON_HLSLI
#define TH_COMMON_HLSLI

cbuffer TH_cbPerObject
{
	matrix TH_worldMatrix, TH_mvMatrix, TH_viewMatrix, TH_normalMatrix, TH_projection;
	float4 TH_argb;
}

cbuffer TH_cbFog
{
	bool TH_fogEnabled;
	struct Fog
	{
		float4 color;
		float start;
		float end;
	} TH_fog;
};

float3 THTransformMVP(float3 position)
{
	float4 v;
	v.xyz = position;
	v.w = 1.0f;
	v = mul(v, TH_mvMatrix);
	v = mul(v, TH_projection);
	return v.xyz / v.w;
}

float3 THTransformMV(float3 position)
{
	float4 v;
	v.xyz = position;
	v.w = 1.0f;
	v = mul(v, TH_mvMatrix);
	return v.xyz / v.w;
}

#endif