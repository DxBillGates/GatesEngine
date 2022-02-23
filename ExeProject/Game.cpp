#include "Game.h"
#include "Header/Util/Random.h"
#include "Header/Util/Utility.h"
#include "Header/Graphics/CBufferStruct.h"
#include "SampleScene.h"

Game::Game()
	: Application()
{
}

Game::Game(const GE::Math::Vector2& size, const std::string& title)
	: Application(size, title)
{
}

Game::~Game()
{
}

bool Game::LoadContents()
{
	Application::LoadContents();
	auto* testScene = sceneManager.AddScene(new SampleScene("SampleScene"));
	sceneManager.ChangeScene("SampleScene");

	return true;
}

bool Game::Initialize()
{
	Application::Initialize();
	return true;
}

bool Game::Update()
{
	Application::Update();
	return true;
}

bool Game::Draw()
{
	GE::ICBufferAllocater* cbufferAllocater = graphicsDevice.GetCBufferAllocater();
	GE::RenderQueue* renderQueue = graphicsDevice.GetRenderQueue();

	graphicsDevice.ClearDefaultRenderTarget(GE::Color::Blue());
	graphicsDevice.SetDefaultRenderTarget();
	//graphicsDevice.ClearLayer("demoLayer");
	//graphicsDevice.SetLayer("demoLayer");
	graphicsDevice.SetShaderResourceDescriptorHeap();
	graphicsDevice.ResetCBufferAllocater();
	graphicsDevice.SetShader("DefaultMeshShader");

	GE::Math::Matrix4x4 modelMatrix = GE::Math::Matrix4x4::Scale({ 25 });
	const GE::CameraInfo& cameraInfo = mainCamera->GetCameraInfo();
	GE::Material material;
	GE::DirectionalLightInfo directionalLight;

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1, &cameraInfo, sizeof(GE::CameraInfo)) });
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2, &material, sizeof(GE::Material)) });
	renderQueue->AddSetConstantBufferInfo({ 3,cbufferAllocater->BindAndAttachData(3, &directionalLight, sizeof(GE::DirectionalLightInfo)) });
	graphicsDevice.DrawMesh("Sphere");

	graphicsDevice.SetShader("DefaultMeshWithTextureShader");
	modelMatrix = GE::Math::Matrix4x4::Identity();
	modelMatrix *= GE::Math::Matrix4x4::Scale({ 50 });
	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	renderQueue->AddSetShaderResource({ 4,graphicsDevice.GetTextureManager()->Get("texture_null")->GetSRVNumber() });
	graphicsDevice.DrawMesh("Skydome");


	graphicsDevice.SetShader("DefaultLineShader");
	modelMatrix = GE::Math::Matrix4x4::Identity();
	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	graphicsDevice.DrawMesh("Grid");

	Application::Draw();

	graphicsDevice.ExecuteRenderQueue();
	graphicsDevice.ScreenFlip();
	return true;
}
