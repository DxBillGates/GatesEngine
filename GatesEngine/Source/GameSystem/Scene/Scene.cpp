#include "..\..\..\Header\GameSystem\Scene\Scene.h"

GE::Scene::Scene() 
	: Scene("unregister name scene")
{
}

GE::Scene::Scene(const std::string& sceneName)
	: name(sceneName)
	, isTerminateApplication(false)
	, audioManager(nullptr)
	, inputDevice(nullptr)
{
}

GE::Scene::~Scene()
{
}

void GE::Scene::Initialize()
{

}

void GE::Scene::Update(float deltaTime)
{
}

void GE::Scene::Draw()
{
}

void GE::Scene::LateDraw()
{
}

const std::string& GE::Scene::GetSceneName()
{
	return name;
}

bool GE::Scene::IsTerminateApplication()
{
	return isTerminateApplication;
}

const GE::ChangeSceneInfo& GE::Scene::IsChangeScene()
{
	return changeSceneInfo;
}

void GE::Scene::SetSceneInitializer(const SceneInitializer& initializer)
{
	audioManager = initializer.audioManager;
	inputDevice = initializer.inputDevice;
	isSetInitializer = true;
}
