#include "..\..\..\Header\GameFramework\Component\BoxCollider.h"
#include "..\..\..\Header\GUI\GUIManager.h"

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

	// sphere model とかぶってしまうため描画オブジェクトより少し大きめに設定
	const float ADD_SCALE = 0.005f;
	Math::Matrix4x4 scaleMatrix = Math::Matrix4x4::Scale(bounds.size + ADD_SCALE);
	Math::Matrix4x4 translateMatrix = Math::Matrix4x4::Translate(bounds.center);
	Math::Matrix4x4 parentMatrix;
	Math::Matrix4x4 localMatrix;
	Math::Matrix4x4 worldMatrix;

	// AABBとOBBでバウンディングボックスに回転行列の有無があるのでここで設定
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

	// 描画コールをキューに積む
	//graphicsDevice->SetDefaultRenderTarget();
	graphicsDevice->SetShader("DefaultLineShader");

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0,&worldMatrix,sizeof(Math::Matrix4x4)) });

	const CameraInfo& cameraInfo = graphicsDevice->GetMainCamera()->GetCameraInfo();
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1,&cameraInfo,sizeof(CameraInfo)) });

	Material material;
	material.color = hitFlagController.GetFlag() ? Color::Red() : Color::Green();
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(Material)) });

	graphicsDevice->DrawMesh("LineCube");
}

void GE::BoxCollider::OnGui()
{
	ImGui::Checkbox("DrawEnabled", &drawEnabled);
	if (ImGui::TreeNode("Bounds"))
	{

		float dragSpeed = 0.1f;
		float minMaxValue = 10000;
		ImGui::DragFloat3("Center", bounds.center.value, dragSpeed, -minMaxValue, minMaxValue);

		float minData[3] = { bounds.min.value[0],bounds.min.value[1],bounds.min.value[2] };
		ImGui::DragFloat3("Min", minData, dragSpeed, -minMaxValue, minMaxValue);

		float maxData[3] = { bounds.max.value[0],bounds.max.value[1],bounds.max.value[2] };
		ImGui::DragFloat3("Max", maxData, dragSpeed, -minMaxValue, minMaxValue);

		ImGui::DragFloat3("Size", bounds.size.value, dragSpeed, 0, minMaxValue);
		ImGui::TreePop();
	}
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
