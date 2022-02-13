#include "Game.h"
#include "Header/Util/Random.h"
#include "Header/Util/Utility.h"
#include "Header/Graphics/CBufferStruct.h"

Game::Game()
	: Application()
{
}

Game::Game(const GE::Math::Vector2& size, const std::string& title)
	: Application(size,title)
{
}

Game::~Game()
{
}

bool Game::LoadContents()
{
	Application::LoadContents();
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
	graphicsDevice.ClearDefaultRenderTarget();
	graphicsDevice.SetDefaultRenderTarget();
	graphicsDevice.SetShaderResourceDescriptorHeap();
	graphicsDevice.ResetCBufferAllocater();
	graphicsDevice.SetShader("DefaultMeshShader");

	GE::Math::Matrix4x4 modelMatrix = GE::Math::Matrix4x4::Scale({ 100 });
	const GE::CameraInfo& cameraInfo = mainCamera->GetCameraInfo();
	GE::Material material;
	GE::DirectionalLightInfo directionalLight;

	graphicsDevice.GetCBufferAllocater()->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4));
	graphicsDevice.GetCBufferAllocater()->BindAndAttachData(1, &cameraInfo, sizeof(GE::CameraInfo));
	graphicsDevice.GetCBufferAllocater()->BindAndAttachData(2, &material, sizeof(GE::Material));
	graphicsDevice.GetCBufferAllocater()->BindAndAttachData(3, &directionalLight, sizeof(GE::DirectionalLightInfo));
	graphicsDevice.GetMeshManager()->Get("Sphere")->Draw();


	modelMatrix = GE::Math::Matrix4x4::Identity();
	modelMatrix *= GE::Math::Matrix4x4::Scale(1000);
	modelMatrix *= GE::Math::Matrix4x4::RotationX(GE::Math::ConvertToRadian(0));
	graphicsDevice.GetCBufferAllocater()->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4));
	graphicsDevice.GetMeshManager()->Get("Plane")->Draw();

	Application::Draw();
	graphicsDevice.ScreenFlip();
	return true;
}
