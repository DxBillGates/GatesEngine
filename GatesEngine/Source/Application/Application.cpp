#include "..\..\Header\Application\Application.h"
#include "..\..\Header\GameSystem\Scene\SampleScene.h"

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

	mainWindow.Create(size,title);
	mainWindow.PreviewWindow();

	inputDevice->Create(mainWindow.GetHandle(), mainWindow.GetHInstance());

	Audio::SetAudioEngine();
}

GE::Application::~Application()
{
}

bool GE::Application::LoadContents()
{
	auto* testBGMData = audioManager.AddAudioData(new AudioData("Resources/Audio/testBGM_sharou.wav"), "testBGMData");
	auto* testBGM = audioManager.AddAudio(new Audio(testBGMData, "testBGM"));
	testBGM->Start();
	testBGM->SetVolume(0.05f);

	auto* testScene = sceneManager.AddScene(new SampleScene("SampleScene"));

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
	return true;
}

bool GE::Application::Draw()
{
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
