#include "..\..\..\Header\GameFramework\Component\SampleComponent.h"
#include "..\..\..\Header\Graphics\CBufferStruct.h"
#include "..\..\..\Header\Util\Utility.h"
#include "..\..\..\Header\Util\Random.h"

GE::SampleComponent::SampleComponent()
	: inputDevice(nullptr)
{
}

GE::SampleComponent::~SampleComponent()
{
}

void GE::SampleComponent::Awake()
{
	Utility::Printf("SampleComponent Awake()\n");
}

void GE::SampleComponent::Start()
{
	Utility::Printf("SampleComponent Start()\n");
	inputDevice = InputDevice::GetInstance();
	random = { RandomMaker::GetFloat(-1,1),RandomMaker::GetFloat(-1,1),RandomMaker::GetFloat(-1,1) };
}

void GE::SampleComponent::Update(float deltaTime)
{
	const Math::Axis& axis = transform->GetMatrix().GetAxis();
	if (inputDevice->GetKeyboard()->CheckHitKey(Keys::SPACE))
	{
		transform->position += axis.y;
	}

	if (inputDevice->GetKeyboard()->CheckPressTrigger(Keys::SPACE))
	{
		Utility::Printf("SampleComponent Update() : press space key\n");
	}

	if (inputDevice->GetMouse()->GetCheckPressTrigger(MouseButtons::LEFT_CLICK))
	{
		Utility::Printf("SampleComponent Update() : press left click\n");
	}

	if (inputDevice->GetXCtrler()->CheckHitButtonTrigger(XInputControllerButton::XINPUT_B))
	{
		Utility::Printf("SampleComponent Update() : press b button\n");
	}

	transform->rotation += random / 100;
}

void GE::SampleComponent::Draw()
{
	const float DRAW_SIZE = 100;
	GE::ICBufferAllocater* cbufferAllocater = graphicsDevice->GetCBufferAllocater();
	GE::RenderQueue* renderQueue = graphicsDevice->GetRenderQueue();

	graphicsDevice->SetShader("DefaultMeshShader");

	transform->scale = DRAW_SIZE;
	Math::Matrix4x4 modelMatrix = transform->GetMatrix();
	Material material;
	material.color = Color::White();

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(Material)) });
	graphicsDevice->DrawMesh("Plane");
}

void GE::SampleComponent::LateDraw()
{
	const float SPRITE_SIZE = 100;

	GE::ICBufferAllocater* cbufferAllocater = graphicsDevice->GetCBufferAllocater();
	GE::RenderQueue* renderQueue = graphicsDevice->GetRenderQueue();

	graphicsDevice->SetShader("DefaultSpriteShader");

	GE::Math::Matrix4x4 modelMatrix = GE::Math::Matrix4x4::Scale({ SPRITE_SIZE });
	GE::Math::Vector2 mousePos = inputDevice->GetMouse()->GetClientMousePos();
	//GE::Utility::Printf("%d,%d\n",(int)mousePos.x, (int)mousePos.y);

	modelMatrix *= GE::Math::Matrix4x4::Translate({ mousePos.x,mousePos.y,0 });
	Material material;
	material.color = Color::White();

	GE::CameraInfo cameraInfo;
	cameraInfo.viewMatrix = GE::Math::Matrix4x4::GetViewMatrixLookTo({ 0,1,0 }, { 0,0,1 }, { 0,1,0 });
	cameraInfo.projMatrix = GE::Math::Matrix4x4::GetOrthographMatrix({ 1920,1080 });

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1, &cameraInfo, sizeof(GE::CameraInfo)) });
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(Material)) });
	graphicsDevice->DrawMesh("2DPlane");
}

void GE::SampleComponent::OnCollision(GameObject* other)
{
	Utility::Printf("SampleComponent OnCollision(GameObject* other) : hit\n");
}

void GE::SampleComponent::OnCollision(ICollider* hitCollider)
{
	Utility::Printf("SampleComponent OnCollision(ICollider* other) : hit\n");
}
