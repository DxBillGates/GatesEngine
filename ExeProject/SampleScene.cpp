#include "SampleScene.h"
#include <GatesEngine/Header\GameFramework\Component\SampleComponent.h>
#include <GatesEngine/Header\GameFramework\Component\SphereCollider.h>
#include <GatesEngine/Header\GameFramework\Component\BoxCollider.h>
#include <GatesEngine/Header\GameFramework\Collision\CollisionManager.h>

SampleScene::SampleScene()
	: SampleScene("SampleScene")
{
}

SampleScene::SampleScene(const std::string& sceneName)
	: Scene(sceneName)
	, col1(nullptr)
	, col2(nullptr)
{
	{
		auto* testObject = gameObjectManager.AddGameObject(new GE::GameObject());
		testObject->SetName("test1");
		testObject->GetTransform()->position = { 1050,0,0 };
		testObject->SetDrawAxisEnabled(true);
		auto* sampleCollider = testObject->AddComponent < GE::SphereCollider >();
		auto* sampleComponent = testObject->AddComponent<GE::SampleComponent>();
		sampleCollider->SetCenter({ 0,0,0 });
		sampleCollider->SetSize({ 2 });
		col1 = sampleCollider;
	}

	{
		auto* testObject = gameObjectManager.AddGameObject(new GE::GameObject());
		testObject->SetName("test2");
		testObject->GetTransform()->position = { 1300,0,0 };
		testObject->SetDrawAxisEnabled(true);
		auto* sampleCollider = testObject->AddComponent<GE::BoxCollider>();
		auto* sampleComponent = testObject->AddComponent<GE::SampleComponent>();
		sampleCollider->SetCenter({ 0,0,0 });
		sampleCollider->SetSize({ 2 });
		sampleCollider->SetType(GE::ColliderType::OBB);
		col2 = sampleCollider;
	}
}

SampleScene::~SampleScene()
{
}

void SampleScene::Initialize()
{
	gameObjectManager.Awake();
	gameObjectManager.Start();
}

void SampleScene::Update(float deltaTime)
{
	gameObjectManager.Update(deltaTime);

	if (GE::CollisionManager::CheckHit(col1, col2))
	{
		col1->Hit(col2, nullptr);
		col2->Hit(col1, nullptr);
	}
}

void SampleScene::Draw()
{
	gameObjectManager.Draw();
}

void SampleScene::LateDraw()
{
	gameObjectManager.LateDraw();
}
