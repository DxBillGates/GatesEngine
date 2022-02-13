#include "DefaultShader.hlsli"

float4 main(VSOutput psInput) : SV_TARGET
{
	float3 lightDir = normalize(worldLightDir.xyz);
	float3 normal = normalize(psInput.normal);

	float3 diff = saturate(dot(-lightDir, normal)) * diffuse.xyz;

	float3 intensity = saturate(ambient.xyz + diff) * worldLightColor.xyz;
	return float4(intensity, alpha.x);
}