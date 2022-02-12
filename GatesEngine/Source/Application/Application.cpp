#include "..\..\Header\Application\Application.h"
#include "..\..\Header\GameFramework\Scene\SampleScene.h"
#include "..\..\Header\Graphics\Shader.h"
#include "..\..\Header\Graphics\RootSignature.h"
#include "..\..\Header\Graphics\GraphicsPipeline.h"
#include "..\..\Header\Graphics\MeshManager.h"
#include "..\..\Header\Graphics\Mesh.h"
#include "..\..\Header\Graphics\MeshData.h"
#include "..\..\Header\Graphics\VertexData.h"
#include "..\..\Header\Graphics\MeshCreater.h"

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

	MeshManager* meshManager = graphicsDevice.GetMeshManager();
	Mesh* mesh;
	// 板ポリ生成
	MeshData<Vertex_UV_Normal> meshDataPlane;
	MeshCreater::CreatePlane(meshDataPlane);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), meshDataPlane);
	meshManager->Add(mesh, "Plane");

	MeshData<Vertex_UV> meshData2DPlane;
	MeshCreater::Create2DPlane(meshData2DPlane);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), meshData2DPlane);
	meshManager->Add(mesh, "2DPlane");

	MeshData<Vertex_UV> meshData2DPlanePivot;
	MeshCreater::Create2DPlane(meshData2DPlanePivot, { 1 }, { 1 }, {-1,0});
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), meshData2DPlanePivot);
	meshManager->Add(mesh, "2DPlanePivot");

	// グリッド生成
	MeshData<Vertex_Color> meshDataGrid;
	MeshCreater::CreateGrid(meshDataGrid);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), meshDataGrid);
	meshManager->Add(mesh, "Grid");

	// lineCube生成
	MeshData<Vertex_Color> meshDataLineCube;
	MeshCreater::CreateLineCube(meshDataLineCube);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), meshDataLineCube);
	meshManager->Add(mesh, "LineCube");

	// lineCircle生成
	MeshData<Vertex_Color> meshDataLineCircle;
	MeshCreater::CreateLineCircle(meshDataLineCircle);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), meshDataLineCircle);
	meshManager->Add(mesh, "LineCircle");

	// model読み込み
	MeshData<Vertex_UV_Normal> modelDataCube;
	MeshCreater::LoadObjModelData("Resources/Model/cube",modelDataCube);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), modelDataCube);
	meshManager->Add(mesh, "Cube");

	MeshData<Vertex_UV_Normal> modelDataSphere;
	MeshCreater::LoadObjModelData("Resources/Model/sphere", modelDataSphere);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), modelDataSphere);
	meshManager->Add(mesh, "Sphere");

	MeshData<Vertex_UV_Normal> modelDataPlatonic;
	MeshCreater::LoadObjModelData("Resources/Model/platonic", modelDataPlatonic);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), modelDataPlatonic);
	meshManager->Add(mesh, "Platonic");

	MeshData<Vertex_UV_Normal> modelDataCorn;
	MeshCreater::LoadObjModelData("Resources/Model/corn", modelDataCorn);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), modelDataCorn);
	meshManager->Add(mesh, "Corn");

	MeshData<Vertex_UV_Normal> modelDataCylinder;
	MeshCreater::LoadObjModelData("Resources/Model/cylinder", modelDataCylinder);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), modelDataCylinder);
	meshManager->Add(mesh, "Cylinder");

	MeshData<Vertex_UV_Normal> modelDataSkydome;
	MeshCreater::LoadObjModelData("Resources/Model/skydome", modelDataSkydome);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), modelDataSkydome);
	meshManager->Add(mesh, "Skydome");

	MeshData<Vertex_UV_Normal> modelDataTorus;
	MeshCreater::LoadObjModelData("Resources/Model/skydome", modelDataTorus);
	mesh = new Mesh();
	mesh->Create(graphicsDevice.GetDevice(), graphicsDevice.GetCmdList(), modelDataTorus);
	meshManager->Add(mesh, "Torus");

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
