#include "common.hlsli"

#define TH_LIGHT_NONE 0
#define TH_LIGHT_AMBIENT 1
#define TH_LIGHT_DIRECTIONAL 2

struct DirectionalLight
{
	float4 color;
	float3 direction;
};

cbuffer TH_cbPerLight
{
	int TH_lightType;
	float4 TH_ambientLight;
	DirectionalLight TH_directionalLight;
}

// directional light shadow maps

#define SHADOW_EPSILON 0.0005f
#define SHADOW_NORMAL_OFFSET 10.0f

matrix TH_lightVP;
Texture2D TH_shadowMap;
int TH_shadowMapWidth, TH_shadowMapHeight;
bool TH_shadowEnabled;

SamplerState TH_shadowSampler
{
	Filter = ANISOTROPIC;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

float __chebyshev(float2 moments, float depth)
{
	float p = (depth <= moments.x) ? 1.0f : 0.0f;
	float variance = moments.y - moments.x * moments.x;
	variance = min(1.0f, max(variance, 0.0f));
	float d = depth - moments.x;
	float p_max = variance / (variance + d * d);
	return max(p, p_max);
}

float __getVSM(in float4 posInShadowMap)
{
	float2 shadowTex = 0.5 * posInShadowMap.xy / posInShadowMap.w + float2(0.5, 0.5);
	shadowTex.y = 1.0f - shadowTex.y;
	float depth = posInShadowMap.z / posInShadowMap.w - SHADOW_EPSILON;

	float4 c = TH_shadowMap.Sample(TH_shadowSampler, shadowTex.xy);
	float2 moments = c.xy;
	return __chebyshev(moments, depth);
}

float THGetLightDensity(in float3 posInWorld, float3 normal, float3 lightDir)
{
	float4 pos;
	pos.xyz = posInWorld + normal * SHADOW_NORMAL_OFFSET * saturate(1.0f - dot(normal, -lightDir));
	pos.w = 1.0f;
	float4 posInShadowMap = mul(pos, TH_lightVP);

	float sum = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			sum += __getVSM(posInShadowMap + float4(i * 1.0f / 1024, j * 1.0f / 1024, 0, 0));
		}
	}
	return sum / 9;

	return __getVSM(posInShadowMap);
}

float4 THAmbientLighting(in float4 material_ambient, float4 diffuse)
{
	return material_ambient * TH_ambientLight * diffuse;
}

float4 THDirectionalLighting(float4 diffuse, float4 specular, float power, float3 normal, float3 viewDir)
{
	normal = normalize(normal);
	viewDir = normalize(viewDir);
	float3 lightDir = TH_directionalLight.direction;
	float cosine = -dot(lightDir, normal);
	if (cosine < 0)
	{
		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	float3 halfAngle = normalize(lightDir + viewDir);
	float4 shaded_diffuse = saturate(float4((TH_directionalLight.color * cosine * diffuse).xyz,
		TH_directionalLight.color.w * diffuse.w));
	float4 shaded_specular = saturate(float4((pow(max(-dot(normal, halfAngle), 0.0f), power) * specular * TH_directionalLight.color).xyz,
		TH_directionalLight.color.w * specular.w));
	return float4(shaded_diffuse.xyz + shaded_specular.xyz, max(shaded_diffuse.w, shaded_specular.w));
}

float4 THShade(float4 ambient, float4 diffuse, float4 specular, float4 emissive,
	float shininess, float3 normal, float3 position)
{
	float4 color;
	switch (TH_lightType)
	{
	case TH_LIGHT_NONE:
		color = diffuse;
		break;
	case TH_LIGHT_AMBIENT:
		color = THAmbientLighting(ambient, diffuse);
		break;
	case TH_LIGHT_DIRECTIONAL:
		color = THDirectionalLighting(diffuse, specular, shininess, normal, position);
		break;
	}

	if (TH_shadowEnabled && TH_lightType == TH_LIGHT_DIRECTIONAL)
	{
		color.xyz *= THGetLightDensity(position, normal, TH_directionalLight.direction);
	}

	if (TH_fogEnabled)
	{
		float4 posInView = mul(float4(position, 1.0f), TH_viewMatrix);
		float distToCamera = length(posInView.xyz);
		float fogLerp = saturate((distToCamera - TH_fog.start) / (TH_fog.end - TH_fog.start)) * TH_fog.color.w;
		color.xyz = lerp(color.xyz, TH_fog.color.xyz, fogLerp);
	}
	return color;
}