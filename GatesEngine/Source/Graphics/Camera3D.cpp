#include "..\..\Header\Graphics\Camera3D.h"

GE::Camera3D::Camera3D()
	: direction(Math::Vector3(0, 0, 1))
	, up(Math::Vector3(0, 1, 0))
	, yaw(0)
	, pitch(0)
	, rotation(Math::Matrix4x4::Identity())
	, windowSize(Math::Vector2(1920,1080))
	, aspect(windowSize.x / windowSize.y)
{
}

void GE::Camera3D::Initialize()
{
	Camera::Initialize();
	direction = Math::Vector3(0, 0, 1);
	up = Math::Vector3(0, 1, 0);
	yaw = 0;
	pitch = 0;
	rotation = Math::Matrix4x4::Identity();
}

void GE::Camera3D::SetWindowSize(const Math::Vector2& size)
{
	windowSize = size;
	aspect = size.x / size.y;
}

void GE::Camera3D::SetAspect(float value)
{
	aspect = value;
}
