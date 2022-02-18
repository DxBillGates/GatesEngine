#include "..\..\..\Header\GameFramework\Component\BoxCollider.h"

GE::BoxCollider::BoxCollider()
	: isSetCenter(false)
{
}

GE::BoxCollider::~BoxCollider()
{
}

void GE::BoxCollider::Awake()
{
	bounds.center = (isSetCenter) ? bounds.center : Math::Vector3();
}

void GE::BoxCollider::Draw()
{
	if (!drawEnabled)return;
	// sphere model とかぶってしまうため描画オブジェクトより少し大きめに設定
	const float ADD_SCALE = 0.005f;
	Math::Matrix4x4 scaleMatrix = Math::Matrix4x4::Scale(bounds.size + ADD_SCALE);
	Math::Matrix4x4 rotateMatrix = localRotation;
	Math::Matrix4x4 translateMatrix = Math::Matrix4x4::Translate(bounds.center);
	Math::Matrix4x4 modelMatrix;
	Material material;
	material.color = hitFlagController.GetFlag() ? Color::Red() : Color::Green();
	const CameraInfo& cameraInfo = graphicsDevice->GetMainCamera()->GetCameraInfo();

	ICBufferAllocater* cbufferAllocater = graphicsDevice->GetCBufferAllocater();
	RenderQueue* renderQueue = graphicsDevice->GetRenderQueue();

	graphicsDevice->SetDefaultRenderTarget();
	graphicsDevice->SetShader("DefaultLineShader");

	Math::Matrix4x4 gameObjectMatrix;
	if (type == ColliderType::AABB)
	{
		gameObjectMatrix = Math::Matrix4x4::Scale(transform->scale) * Math::Matrix4x4::Translate(transform->position);
		modelMatrix = scaleMatrix * translateMatrix * transform->GetMatrix();
	}
	else
	{
		modelMatrix = scaleMatrix * localRotation * translateMatrix * transform->GetMatrix();
	}
	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0,&modelMatrix,sizeof(Math::Matrix4x4)) });
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1,&cameraInfo,sizeof(CameraInfo)) });
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(Material)) });
	graphicsDevice->DrawMesh("LineCube");
}

void GE::BoxCollider::SetSize(const Math::Vector3& size)
{
	bounds.size = size;
}

void GE::BoxCollider::SetCenter(const Math::Vector3& pos)
{
	isSetCenter = true;
	bounds.center = pos;
}

void GE::BoxCollider::DrawEnabled(bool flag)
{
	drawEnabled = flag;
}

void GE::BoxCollider::SetType(ColliderType type)
{
	this->type = type;
}
