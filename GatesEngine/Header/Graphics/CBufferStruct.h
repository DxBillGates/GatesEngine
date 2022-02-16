#pragma once
#include "..\Util\Math\Matrix4.h"
#include "..\Util\Math\Vector4.h"

namespace GE
{
	struct ModelInfo
	{
		Math::Matrix4x4 modelMatrix = Math::Matrix4x4::Identity();
	};

	struct CameraInfo
	{
		Math::Matrix4x4 viewMatrix;
		Math::Matrix4x4 projMatrix;
		Math::Matrix4x4 billboard = Math::Matrix4x4::Identity();
		Math::Vector4 cameraPos = { 0 };
		Math::Vector4 cameraDir = { 0 };
	};

	struct Material
	{
		Math::Vector4 ambient = { 0.0f };
		Math::Vector4 diffuse = { 1 };
		Math::Vector4 specular = { 50 };
		Math::Vector4 alpha = { 1 };
		Math::Vector4 threshold = { 1 };
	};

	struct DirectionalLightInfo
	{
		Math::Vector4 worldLightDir = { 0,-1,0,0 };
		Math::Vector4 worldLightColor = { 1 };
	};
}