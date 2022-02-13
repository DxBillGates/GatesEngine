struct VSInput
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float4 worldPosition : WORLD_POSITION;
};

cbuffer ModelInfo : register(b0)
{
	matrix modelMatrix;
}

cbuffer CameraInfo : register(b1)
{
	matrix viewMatrix;
	matrix projMatrix;
	matrix billboard;
	float4 cameraPos;
	float4 cameraDir;
}

cbuffer Material : register(b2)
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 alpha;
	float4 threshold;
}

cbuffer DirectionalLightInfo : register(b3)
{
	float4 worldLightDir;
	float4 worldLightColor;
}

float3 GetPosition(matrix mat)
{
	return float3(-mat[0][3], -mat[1][3], -mat[2][3]);
}