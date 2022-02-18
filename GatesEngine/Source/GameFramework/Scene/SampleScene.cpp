#include "..\..\..\Header\GameFramework\Scene\SampleScene.h"
#include "..\..\..\Header\GameFramework\Component\SampleComponent.h"
#include "..\..\..\Header\GameFramework\Component\SphereCollider.h"
#include "..\..\..\Header\GameFramework\Component\BoxCollider.h"

GE::SampleScene::SampleScene()
	: Scene()
{
}

GE::SampleScene::SampleScene(const std::string& sceneName)
	: Scene(sceneName)
{
	auto* testObject = gameObjectManager.AddGameObject(new GameObject());
	testObject->GetTransform()->position = { 1000,0,0 };
	auto* sampleComponent = testObject->AddComponent<SampleComponent>();
	auto* sampleCollider = testObject->AddComponent<BoxCollider>();
	sampleCollider->SetCenter({ 10,0,0 });
	sampleCollider->SetLocalRotation({ 0,1,0 }, 180);
	sampleCollider->SetType(ColliderType::OBB);

	ICollider* col = sampleCollider;
	const Math::Axis& axis = col->GetAxis();
}

GE::SampleScene::~SampleScene()
{
}

void GE::SampleScene::Initialize()
{
	gameObjectManager.Awake();
	gameObjectManager.Start();
}

void GE::SampleScene::Update(float deltaTime)
{
	gameObjectManager.Update(deltaTime);
}

void GE::SampleScene::Draw()
{
	gameObjectManager.Draw();
}

void GE::SampleScene::LateDraw()
{
	gameObjectManager.LateDraw();
}
