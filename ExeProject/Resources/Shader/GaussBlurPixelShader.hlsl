#include "GaussBlurShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);

float4 main(DefaultSpriteVSOutput input) : SV_TARGET
{
	float4 result = 0;

	for (int i = 0; i < 16; ++i)
	{
		result += data[i].z * tex.Sample(clampPointSampler, input.uv + data[i].xy);
	}

	return float4(result.rgb,1);
}