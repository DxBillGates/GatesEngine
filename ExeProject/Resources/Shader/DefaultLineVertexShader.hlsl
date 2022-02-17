#include "DefaultShader.hlsli"

DefaultLineVSOutput main(DefaultLineVSInput input)
{
	DefaultLineVSOutput output;
	output.svpos = mul(projMatrix, mul(viewMatrix, mul(modelMatrix, input.pos)));
	output.pos = input.pos;
	output.color = input.color;
	return output;
}