#include "DefaultShader.hlsli"

float4 main(DefaultSpriteVSOutput input) : SV_TARGET
{
	return float4(color);
}