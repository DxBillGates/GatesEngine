#include "DefaultShader.hlsli"

DefaultSpriteVSOutput main(DefaultSpriteVSInput input)
{
	DefaultSpriteVSOutput output;
	output.svpos = mul(projMatrix, mul(viewMatrix, mul(billboard, mul(modelMatrix, input.pos))));
	output.uv = input.uv;
	return output;
}