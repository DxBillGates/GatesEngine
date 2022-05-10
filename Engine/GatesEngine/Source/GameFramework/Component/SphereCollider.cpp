#include "..\..\..\Header\GameFramework\Component\SphereCollider.h"
#include "..\..\..\Header\Graphics\CBufferStruct.h"

GE::SphereCollider::SphereCollider()
	: isSetCenter(false)
	, r(1)
{
	type = ColliderType::SPHERE;
}

GE::SphereCollider::~SphereCollider()
{
}

void GE::SphereCollider::Awake()
{
	type = ColliderType::SPHERE;
	SetSize(2);
	bounds.center = (isSetCenter) ? bounds.center : Math::Vector3(0,0,0);
}

void GE::SphereCollider::Draw()
{
	if (!drawEnabled)return;
	ICBufferAllocater* cbufferAllocater = graphicsDevice->GetCBufferAllocater();
	RenderQueue* renderQueue = graphicsDevice->GetRenderQueue();

	// sphere model とかぶってしまうため描画オブジェクトより少し大きめに設定
	const float ADD_SCALE = 0.005f;
	Math::Matrix4x4 scaleMatrix = Math::Matrix4x4::Scale(r + ADD_SCALE);
	Math::Matrix4x4 rotateMatrix = Math::Matrix4x4::Identity();
	Math::Matrix4x4 translateMatrix = Math::Matrix4x4::Translate(bounds.center);
	Math::Matrix4x4 worldMatrix;


	graphicsDevice->SetDefaultRenderTarget();
	graphicsDevice->SetShader("DefaultLineShader");

	worldMatrix = scaleMatrix * rotateMatrix * translateMatrix * transform->GetMatrix();
	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0,&worldMatrix,sizeof(Math::Matrix4x4)) });

	const CameraInfo& cameraInfo = graphicsDevice->GetMainCamera()->GetCameraInfo();
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1,&cameraInfo,sizeof(CameraInfo)) });

	Material material;
	material.color = hitFlagController.GetFlag() ? Color::Red() : Color::Green();
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(Material)) });

	graphicsDevice->DrawMesh("LineCircle");

	rotateMatrix = Math::Matrix4x4::RotationX(Math::ConvertToRadian(90));
	worldMatrix = scaleMatrix * rotateMatrix * translateMatrix * transform->GetMatrix();
	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0,&worldMatrix,sizeof(Math::Matrix4x4)) });
	graphicsDevice->DrawMesh("LineCircle");

	rotateMatrix = Math::Matrix4x4::RotationZ(Math::ConvertToRadian(90));
	worldMatrix = scaleMatrix * rotateMatrix * translateMatrix * transform->GetMatrix();
	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0,&worldMatrix,sizeof(Math::Matrix4x4)) });
	graphicsDevice->DrawMesh("LineCircle");

}

void GE::SphereCollider::SetSize(float size)
{
	bounds.size = size;
	r = size;
}

void GE::SphereCollider::SetCenter(const Math::Vector3& pos)
{
	isSetCenter = true;
	bounds.center = pos;
}

void GE::SphereCollider::DrawEnabled(bool flag)
{
	drawEnabled = true;
}
