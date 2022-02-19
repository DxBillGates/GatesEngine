#include "..\..\..\Header\GameFramework\Component\BoxCollider.h"

GE::BoxCollider::BoxCollider()
	: isSetCenter(false)
{
	type = ColliderType::OBB;
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
	ICBufferAllocater* cbufferAllocater = graphicsDevice->GetCBufferAllocater();
	RenderQueue* renderQueue = graphicsDevice->GetRenderQueue();

	// sphere model �Ƃ��Ԃ��Ă��܂����ߕ`��I�u�W�F�N�g��菭���傫�߂ɐݒ�
	const float ADD_SCALE = 0.005f;
	Math::Matrix4x4 scaleMatrix = Math::Matrix4x4::Scale(bounds.size + ADD_SCALE);
	Math::Matrix4x4 translateMatrix = Math::Matrix4x4::Translate(bounds.center);
	Math::Matrix4x4 parentMatrix;
	Math::Matrix4x4 localMatrix;
	Math::Matrix4x4 worldMatrix;

	// AABB��OBB�Ńo�E���f�B���O�{�b�N�X�ɉ�]�s��̗L��������̂ł����Őݒ�
	if (type == ColliderType::AABB)
	{
		parentMatrix = Math::Matrix4x4::Scale(transform->scale) * Math::Matrix4x4::Translate(transform->position);
		localMatrix = scaleMatrix * translateMatrix;
		worldMatrix = localMatrix * parentMatrix;
	}
	else
	{
		localMatrix = scaleMatrix * localRotation * translateMatrix;
		worldMatrix = localMatrix * transform->GetMatrix();
	}

	// �`��R�[�����L���[�ɐς�
	graphicsDevice->SetDefaultRenderTarget();
	graphicsDevice->SetShader("DefaultLineShader");

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0,&worldMatrix,sizeof(Math::Matrix4x4)) });

	const CameraInfo& cameraInfo = graphicsDevice->GetMainCamera()->GetCameraInfo();
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1,&cameraInfo,sizeof(CameraInfo)) });

	Material material;
	material.color = hitFlagController.GetFlag() ? Color::Red() : Color::Green();
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
