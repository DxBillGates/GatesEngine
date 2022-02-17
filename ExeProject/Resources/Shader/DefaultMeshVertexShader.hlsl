#include "DefaultShader.hlsli"

DefaultMeshVSOutput main(DefaultMeshVSInput vsInput)
{
	DefaultMeshVSOutput output;
	output.svpos = mul(projMatrix, mul(viewMatrix, mul(billboard, mul(modelMatrix, vsInput.pos))));
	output.uv = vsInput.uv;
	output.normal = mul(billboard, mul(modelMatrix, float4(vsInput.normal,0))).xyz;
	output.worldPosition = mul(modelMatrix, vsInput.pos);
	return output;
}