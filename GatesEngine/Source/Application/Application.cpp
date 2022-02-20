#include "..\..\Header\Application\Application.h"
#include "..\..\Header\GameFramework\Scene\SampleScene.h"
#include "..\..\Header\Graphics\Shader.h"
#include "..\..\Header\Graphics\RootSignature.h"
#include "..\..\Header\Graphics\GraphicsPipeline.h"
#include "..\..\Header\Graphics\Mesh.h"
#include "..\..\Header\Graphics\MeshData.h"
#include "..\..\Header\Graphics\VertexData.h"
#include "..\..\Header\Graphics\MeshCreater.h"
#include "..\..\Header\Graphics\Camera3DDebug.h"
#include "..\..\Header\Graphics\RenderTexture.h"
#include "..\..\Header\Graphics\DepthTexture.h"
#include "..\..\Header\Graphics\Layer.h"
#include "..\..\Header\Graphics\Texture.h"
#include "..\..\Header\GameFramework\GameObject\GameObject.h"

GE::Application::Application()
	: Application(Math::Vector2(1920,1080),"no title")
{
}

GE::Application::Application(const Math::Vector2& size, const std::string& title)
	: timer(Utility::Timer())
	, mainWindow(Window())
	, inputDevice(InputDevice::GetInstance())
	, audioManager(AudioManager())
	, sceneManager(SceneManager())
	, graphicsDevice(GraphicsDeviceDx12())
	, mainCamera(nullptr)
{
	timer.SetFrameRate(144);
	timer.SetIsShow(false);

	mainWindow.Create(size,title);
	mainWindow.PreviewWindow();

	inputDevice->Create(mainWindow.GetHandle(), mainWindow.GetHInstance());
	graphicsDevice.Create(size, mainWindow.GetHandle());

	mainCamera = new Camera3DDebug();

	graphicsDevice.SetMainCamera(mainCamera);
	GameObject::SetGraphicsDevice(&graphicsDevice);
}

GE::Application::~Application()
{
	delete mainCamera;
}

bool GE::Application::LoadContents()
{
	// sample bgm ���[�h���Đ�
	auto* testBGMData = audioManager.AddAudioData(new AudioData("Resources/Audio/testBGM_sharou.wav"), "testBGMData");
	auto* testBGM = audioManager.AddAudio(new Audio(testBGMData, "testBGM"));
	testBGM->Start();
	testBGM->SetVolume(0.05f);

	auto* testScene = sceneManager.AddScene(new SampleScene("SampleScene"));
	sceneManager.ChangeScene("SampleScene");

	auto* device = graphicsDevice.GetDevice();
	auto* cmdList = graphicsDevice.GetCmdList();
	auto* shaderResourceHeap = graphicsDevice.GetShaderResourceHeap();

	auto* meshManager = graphicsDevice.GetMeshManager();
	Mesh* mesh;
	// �|������
	MeshData<Vertex_UV_Normal> meshDataPlane;
	MeshCreater::CreatePlane(meshDataPlane);
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshDataPlane);
	meshManager->Add(mesh, "Plane");

	MeshData<Vertex_UV> meshData2DPlane;
	MeshCreater::Create2DPlane(meshData2DPlane);
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshData2DPlane);
	meshManager->Add(mesh, "2DPlane");

	MeshData<Vertex_UV> meshData2DPlanePivot;
	MeshCreater::Create2DPlane(meshData2DPlanePivot, { 1 }, { 1 }, { -1,0 });
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshData2DPlanePivot);
	meshManager->Add(mesh, "2DPlanePivot");

	// �O���b�h����
	MeshData<Vertex_Color> meshDataGrid;
	MeshCreater::CreateGrid(meshDataGrid);
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshDataGrid);
	meshManager->Add(mesh, "Grid");

	// lineCube����
	MeshData<Vertex_Color> meshDataLineCube;
	MeshCreater::CreateLineCube(meshDataLineCube);
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshDataLineCube);
	meshManager->Add(mesh, "LineCube");

	// lineCircle����
	MeshData<Vertex_Color> meshDataLineCircle;
	MeshCreater::CreateLineCircle(meshDataLineCircle);
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshDataLineCircle);
	meshManager->Add(mesh, "LineCircle");

	// line����
	MeshData<Vertex_Color> meshDataLine;
	MeshCreater::CreateLine(meshDataLine);
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshDataLine);
	meshManager->Add(mesh, "Line");

	// lineAxis����
	MeshData<Vertex_Color> meshDataLineAxis;
	MeshCreater::CreateLineAxis(meshDataLineAxis);
	mesh = new Mesh();
	mesh->Create(device, cmdList, meshDataLineAxis);
	meshManager->Add(mesh, "LineAxis");

	// model�ǂݍ���
	MeshData<Vertex_UV_Normal> modelDataCube;
	MeshCreater::LoadObjModelData("Resources/Model/cube", modelDataCube);
	mesh = new Mesh();
	mesh->Create(device, cmdList, modelDataCube);
	meshManager->Add(mesh, "Cube");

	MeshData<Vertex_UV_Normal> modelDataSphere;
	MeshCreater::LoadObjModelData("Resources/Model/sphere", modelDataSphere);
	mesh = new Mesh();
	mesh->Create(device, cmdList, modelDataSphere);
	meshManager->Add(mesh, "Sphere");

	MeshData<Vertex_UV_Normal> modelDataPlatonic;
	MeshCreater::LoadObjModelData("Resources/Model/platonic", modelDataPlatonic);
	mesh = new Mesh();
	mesh->Create(device, cmdList, modelDataPlatonic);
	meshManager->Add(mesh, "Platonic");

	MeshData<Vertex_UV_Normal> modelDataCorn;
	MeshCreater::LoadObjModelData("Resources/Model/corn", modelDataCorn);
	mesh = new Mesh();
	mesh->Create(device, cmdList, modelDataCorn);
	meshManager->Add(mesh, "Corn");

	MeshData<Vertex_UV_Normal> modelDataCylinder;
	MeshCreater::LoadObjModelData("Resources/Model/cylinder", modelDataCylinder);
	mesh = new Mesh();
	mesh->Create(device, cmdList, modelDataCylinder);
	meshManager->Add(mesh, "Cylinder");

	MeshData<Vertex_UV_Normal> modelDataSkydome;
	MeshCreater::LoadObjModelData("Resources/Model/skydome", modelDataSkydome);
	mesh = new Mesh();
	mesh->Create(device, cmdList, modelDataSkydome);
	meshManager->Add(mesh, "Skydome");

	MeshData<Vertex_UV_Normal> modelDataTorus;
	MeshCreater::LoadObjModelData("Resources/Model/skydome", modelDataTorus);
	mesh = new Mesh();
	mesh->Create(device, cmdList, modelDataTorus);
	meshManager->Add(mesh, "Torus");

	// texture load
	auto* textureManager = graphicsDevice.GetTextureManager();
	Texture* nullTexture = new Texture();
	nullTexture->Load("texture_null.png", device, shaderResourceHeap);
	textureManager->Add(nullTexture, "texture_null");

	// shader compile
	Shader defaultMeshVertexShader, defaultMeshPixelShader;
	defaultMeshVertexShader.CompileShaderFileWithoutFormat(L"DefaultMeshVertexShader", "vs_5_0");
	defaultMeshPixelShader.CompileShaderFileWithoutFormat(L"DefaultMeshPixelShader", "ps_5_0");
	Shader defaultLineVertexShader, defaultLinePixelShader;
	defaultLineVertexShader.CompileShaderFileWithoutFormat(L"DefaultLineVertexShader", "vs_5_0");
	defaultLinePixelShader.CompileShaderFileWithoutFormat(L"DefaultLinePixelShader", "ps_5_0");
	Shader defaultMeshWithTexturePixelShader;
	defaultMeshWithTexturePixelShader.CompileShaderFileWithoutFormat(L"DefaultMeshWithTexturePixelShader", "ps_5_0");
	Shader defaultSpriteVertexShader, defaultSpritePixelShader;
	defaultSpriteVertexShader.CompileShaderFileWithoutFormat(L"DefaultSpriteVertexShader", "vs_5_0");
	defaultSpritePixelShader.CompileShaderFileWithoutFormat(L"DefaultSpritePixelShader", "ps_5_0");
	Shader gaussBlurPixelShader;
	gaussBlurPixelShader.CompileShaderFileWithoutFormat(L"GaussBlurPixelShader", "ps_5_0");

	// rootSignature�쐬
	auto* rootSignatureManager = graphicsDevice.GetRootSignatureManager();
	RootSignature* defaultMeshRootSignature = new RootSignature();
	defaultMeshRootSignature->Create(device, { DescriptorRangeType::CBV,DescriptorRangeType::CBV,DescriptorRangeType::CBV,DescriptorRangeType::CBV });
	rootSignatureManager->Add(defaultMeshRootSignature, "CBV4");
	// texture �t�����[�g�V�O�l�`��
	RootSignature* defaultMeshWithOneSrvRootSignature = new RootSignature();
	defaultMeshWithOneSrvRootSignature->Create(device, { DescriptorRangeType::CBV,DescriptorRangeType::CBV,DescriptorRangeType::CBV,DescriptorRangeType::CBV,DescriptorRangeType::SRV });
	rootSignatureManager->Add(defaultMeshWithOneSrvRootSignature, "CBV4SRV1");
	// cbv5srv1���[�g�V�O�l�`��
	RootSignature* cbv5srv1RootSignature = new RootSignature();
	cbv5srv1RootSignature->Create(device, { DescriptorRangeType::CBV,DescriptorRangeType::CBV ,DescriptorRangeType::CBV ,DescriptorRangeType::CBV ,DescriptorRangeType::CBV ,DescriptorRangeType::SRV });
	rootSignatureManager->Add(cbv5srv1RootSignature, "CBV5SRV1");

	// demo graphicsPipeline�쐬
	GraphicsPipelineInfo pipelineInfo = GraphicsPipelineInfo();
	auto* graphicsPipelineManager = graphicsDevice.GetGraphicsPipelineManager();
	GraphicsPipeline* defaultMeshPipline = new GraphicsPipeline({ &defaultMeshVertexShader,nullptr,nullptr,nullptr,&defaultMeshPixelShader });
	defaultMeshPipline->Create(device, { GraphicsPipelineInputLayout::POSITION,GraphicsPipelineInputLayout::UV ,GraphicsPipelineInputLayout::NORMAL }, defaultMeshRootSignature, pipelineInfo);
	graphicsPipelineManager->Add(defaultMeshPipline, "DefaultMeshShader");
	// line shader
	pipelineInfo.topologyType = GraphicsPipelinePrimitiveTopolotyType::LINE;
	GraphicsPipeline* dafaultLinePipeline = new GraphicsPipeline({ &defaultLineVertexShader,nullptr,nullptr,nullptr,&defaultLinePixelShader });
	dafaultLinePipeline->Create(device, { GraphicsPipelineInputLayout::POSITION,GraphicsPipelineInputLayout::COLOR }, defaultMeshRootSignature, pipelineInfo);
	graphicsPipelineManager->Add(dafaultLinePipeline, "DefaultLineShader");
	// texture draw shader
	pipelineInfo.topologyType = GraphicsPipelinePrimitiveTopolotyType::TRIANGLE;
	GraphicsPipeline* dafaultMeshWithTexturePipeline = new GraphicsPipeline({ &defaultMeshVertexShader,nullptr,nullptr,nullptr,&defaultMeshWithTexturePixelShader });
	dafaultMeshWithTexturePipeline->Create(device, { GraphicsPipelineInputLayout::POSITION,GraphicsPipelineInputLayout::UV ,GraphicsPipelineInputLayout::NORMAL }, defaultMeshWithOneSrvRootSignature, pipelineInfo);
	graphicsPipelineManager->Add(dafaultMeshWithTexturePipeline, "DefaultMeshWithTextureShader");
	// default sprite shader
	pipelineInfo.topologyType = GraphicsPipelinePrimitiveTopolotyType::TRIANGLE;
	pipelineInfo.isUseDepthStencil = false;
	GraphicsPipeline* dafaultSpritePipeline = new GraphicsPipeline({ &defaultSpriteVertexShader,nullptr,nullptr,nullptr,&defaultSpritePixelShader });
	dafaultSpritePipeline->Create(device, { GraphicsPipelineInputLayout::POSITION,GraphicsPipelineInputLayout::UV }, defaultMeshRootSignature, pipelineInfo);
	graphicsPipelineManager->Add(dafaultSpritePipeline, "DefaultSpriteShader");
	// gauss blur shader
	GraphicsPipeline* gaussBlurPipeline = new GraphicsPipeline({ &defaultSpriteVertexShader,nullptr,nullptr,nullptr,&gaussBlurPixelShader });
	gaussBlurPipeline->Create(device, { GraphicsPipelineInputLayout::POSITION,GraphicsPipelineInputLayout::UV }, cbv5srv1RootSignature, pipelineInfo);
	graphicsPipelineManager->Add(gaussBlurPipeline, "GaussBlurShader");

	// demo layer�쐬
	auto* layerManager = graphicsDevice.GetLayerManager();
	RenderTexture* demoRenderTexture = new RenderTexture();
	DepthTexture* demoDepthTexture = new DepthTexture();
	demoRenderTexture->Create(device,shaderResourceHeap, mainWindow.GetWindowSize(), Color::Black());
	demoDepthTexture->Create(device, shaderResourceHeap, mainWindow.GetWindowSize());
	layerManager->Add(new Layer(demoRenderTexture,demoDepthTexture),"demoLayer");


	return true;
}

bool GE::Application::Initialize()
{
	SceneInitializer sceneInitializer = { &audioManager,inputDevice,&graphicsDevice };
	sceneManager.Initialize(sceneInitializer);

	mainCamera->Initialize();
	return true;
}

bool GE::Application::Update()
{
	sceneManager.Update(timer.GetElapsedTime());
	mainCamera->Update();
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

		if (!mainWindow.ProcessMessage())return 0;
	}

	return 0;
}
