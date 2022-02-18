#include "..\..\..\Header\GameFramework\Scene\SampleScene.h"
#include "..\..\..\Header\GameFramework\Component\SampleComponent.h"
#include "..\..\..\Header\GameFramework\Component\SphereCollider.h"
#include "..\..\..\Header\GameFramework\Component\BoxCollider.h"
#include "..\..\..\Header\GameFramework\Collision\CollisionManager.h"

GE::SampleScene::SampleScene()
	: Scene()
{
}

GE::SampleScene::SampleScene(const std::string& sceneName)
	: Scene(sceneName)
{
	{
		auto* testObject = gameObjectManager.AddGameObject(new GameObject());
		testObject->GetTransform()->position = { 950,0,0 };
		auto* sampleComponent = testObject->AddComponent<SampleComponent>();
		auto* sampleCollider = testObject->AddComponent<SphereCollider>();
		sampleCollider->SetCenter({ 0,0,0 });
		sampleCollider->SetSize({ 2 });
		sampleCollider->SetLocalRotation({ 0,40,78 });
		//sampleCollider->SetType(ColliderType::AABB);
		col1 = sampleCollider;
	}

	{
		auto* testObject = gameObjectManager.AddGameObject(new GameObject());
		testObject->GetTransform()->position = { 1250,0,0 };
		auto* sampleComponent = testObject->AddComponent<SampleComponent>();
		auto* sampleCollider = testObject->AddComponent<SphereCollider>();
		sampleCollider->SetCenter({ 0,0,0 });
		sampleCollider->SetSize({ 2 });
		sampleCollider->SetLocalRotation({ 90,90,0 });
		//sampleCollider->SetType(ColliderType::AABB);
		col2 = sampleCollider;
	}
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

	col1->GetParent()->position.x += 0.1f;
	if (CollisionManager::CheckHit(col1, col2))
	{
		col1->Hit();
		col2->Hit();
	}
}

void GE::SampleScene::Draw()
{
	gameObjectManager.Draw();
}

void GE::SampleScene::LateDraw()
{
	gameObjectManager.LateDraw();
}
