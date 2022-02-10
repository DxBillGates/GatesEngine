#include "..\..\Header\Application\Application.h"
#include "..\..\Header\GameFramework\Scene\SampleScene.h"
#include "..\..\Header\Graphics\Shader.h"
#include "..\..\Header\Graphics\RootSignature.h"
#include "..\..\Header\Graphics\GraphicsPipeline.h"

GE::Application::Application()
	: Application(Math::Vector2(1920,1080),"no title")
{
}

GE::Application::Application(const Math::Vector2& size, const std::string& title)
	: timer(Util::Timer())
	, mainWindow(Window())
	, inputDevice(InputDevice::GetInstance())
	, audioManager(AudioManager())
{
	timer.SetFrameRate(144);
	timer.SetIsShow(false);

	mainWindow.Create(size,title);
	mainWindow.PreviewWindow();

	inputDevice->Create(mainWindow.GetHandle(), mainWindow.GetHInstance());
	graphicsDevice.Create(size, mainWindow.GetHandle());

	Audio::SetAudioEngine();
}

GE::Application::~Application()
{
}

bool GE::Application::LoadContents()
{
	// sample bgm ロード＆再生
	auto* testBGMData = audioManager.AddAudioData(new AudioData("Resources/Audio/testBGM_sharou.wav"), "testBGMData");
	auto* testBGM = audioManager.AddAudio(new Audio(testBGMData, "testBGM"));
	testBGM->Start();
	testBGM->SetVolume(0.05f);

	auto* testScene = sceneManager.AddScene(new SampleScene("SampleScene"));
	sceneManager.ChangeScene("SampleScene");

	//// demo rootSignature作成
	//auto* rootSignatureManager = graphicsDevice.GetRootSignatureManager();
	//RootSignature* testRootSignature = new RootSignature();
	//testRootSignature->Create(graphicsDevice.GetDevice(), { DescriptorRangeType::CBV,DescriptorRangeType::CBV,DescriptorRangeType::SRV });
	//rootSignatureManager->Add(testRootSignature, "CBVCBVSRV");

	//// demo graphicsPipeline作成
	//auto* graphicsPipelineManager = graphicsDevice.GetGraphicsPipelineManager();
	//Shader testVShader;
	//testVShader.CompileShaderFile(L"testVS.hlsl", "vs_5_0");
	//Shader testPShader;
	//testPShader.CompileShaderFile(L"testPS.hlsl", "ps_5_0");
	//GraphicsPipeline* testPipeline = new GraphicsPipeline({ &testVShader,nullptr,nullptr,nullptr,&testPShader });
	//testPipeline->Create(graphicsDevice.GetDevice(), {GraphicsPipelineInputLayout::POSITION},testRootSignature, {});
	//graphicsPipelineManager->Add(testPipeline, "testShader");

	return true;
}

bool GE::Application::Initialize()
{
	SceneInitializer sceneInitializer = { &audioManager,inputDevice };
	sceneManager.Initialize(sceneInitializer);

	return true;
}

bool GE::Application::Update()
{
	sceneManager.Update(timer.GetElapsedTime());
	return true;
}

bool GE::Application::Draw()
{
	sceneManager.Draw();
	sceneManager.LateDraw();
	return true;
}

int GE::Application::Run()
{
	if (!LoadContents())return -1;

	inputDevice->Initialize();
	if (!Initialize())return -1;

	while (!inputDevice->GetKeyboard()->CheckPressTrigger(GE::Keys::ESC))
	{
		if (timer.Update())continue;
		inputDevice->Update();
		if (!Update())return -1;
		if (!Draw())return -1;

		if (!mainWindow.ProcessMessage())return -1;
	}

	return 0;
}
