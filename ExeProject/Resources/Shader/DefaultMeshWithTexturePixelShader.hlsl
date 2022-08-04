#include "DefaultShader.hlsli"

Texture2D<float4> tex : register(t0);

float4 main(DefaultMeshVSOutput psInput) : SV_TARGET
{
	float4 texColor = tex.Sample(wrapPointSampler,psInput.uv);
	return texColor;
}