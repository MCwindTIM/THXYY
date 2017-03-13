struct Material
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 emmisive;
	float power;
};

struct DirectionalLight
{
	float4 color;
	float3 direction;
};

struct VertexIn
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

struct VertexOut
{
	float4 sv_position : POSITION;
	float4 positionInView : TEXCOORD2;
	float3 normal : TEXCOORD1;
	float2 texCoord : TEXCOORD0;
};

struct PixelIn
{
	float4 positionInView : TEXCOORD2;
	float3 normal : TEXCOORD1;
	float2 texCoord : TEXCOORD0;
};

Material material;
DirectionalLight directionalLight;
float4 ambientLight;

float4 ambientLighting(in float4 color)
{
	return color * material.ambient * ambientLight;
}

float4 directionalLighting(float4 diffuse, float4 specular, float power, float3 normal, float3 viewDir)
{
	normal = normalize(normal);
	float3 lightDir = normalize(directionalLight.direction);
	float4 result;
	float cosine = -dot(lightDir, normal);
	if (cosine < 0)
	{
		result.x = result.y = result.z = 0;
		result.w = 1;
		return result;
	}
	float3 reflect = lightDir + 2 * normal;
	float3 halfAngle = normalize(lightDir + viewDir);
	return directionalLight.color * cosine * diffuse  + pow(-dot(normal, halfAngle), power) * specular;
}

float4 shadeWithDirectional(float4 color, PixelIn input)
{
	return color * directionalLighting(material.diffuse, material.specular, material.power, input.normal, input.positionInView);
}