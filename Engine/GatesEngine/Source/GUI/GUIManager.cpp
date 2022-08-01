#include "../../Header/GUI/GUIManager.h"

bool GE::GUIManager::isInitialize = false;
GE::IGraphicsDeviceDx12* GE::GUIManager::pGraphicsDevice = nullptr;

void GE::GUIManager::Initialize(HWND hwnd, IGraphicsDeviceDx12* graphicsDevice)
{
	if (!graphicsDevice)
	{
		isInitialize = false;
		return;
	}

	IMGUI_CHECKVERSION();
	if (!ImGui::CreateContext())
	{
		isInitialize = false;
		return;
	}

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// キーボード操作を可能に
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// ドッキング可能に
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	// ImGuiのWindow色スタイルを設定
	ImGui::StyleColorsDark();

	// imguiで使うheapの設定
	auto heap = graphicsDevice->GetShaderResourceHeap();
	Math::Vector3 willUseDescriptorSize = heap->GetWillUseShaderResourceCount();
	int endOffset = willUseDescriptorSize.x + willUseDescriptorSize.y + willUseDescriptorSize.z - 1;

	auto cpuHandle = heap->GetCPUHandle();
	cpuHandle.ptr += heap->GetDescriptorHandleIncrementSize() * endOffset;
	auto gpuHandle = heap->GetGPUHandle();
	gpuHandle.ptr += heap->GetDescriptorHandleIncrementSize() * endOffset;

	// imguiの初期化
	bool isImGuiInitialize = false;
	isImGuiInitialize = ImGui_ImplWin32_Init(hwnd);
	isImGuiInitialize = ImGui_ImplDX12_Init(graphicsDevice->GetDevice(), 2, DXGI_FORMAT_R8G8B8A8_UNORM, heap->GetHeap(), cpuHandle, gpuHandle);

	if (isImGuiInitialize == false)
	{
		isInitialize = false;
		return;
	}

	isInitialize = true;
	pGraphicsDevice = graphicsDevice;
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT GE::GUIManager::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
}

GE::IGraphicsDeviceDx12* GE::GUIManager::GetGraphicsDevice()
{
	return pGraphicsDevice;
}

void GE::GUIManager::Finalize()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void GE::GUIManager::StartFrame(bool isShowDemo)
{
	if (isInitialize == false)return;

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (isShowDemo)
	{
		bool isOpen = true;
		ImGui::ShowDemoWindow(&isOpen);
	}
}

void GE::GUIManager::EndFrame()
{
	if (isInitialize == false)return;

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), pGraphicsDevice->GetCmdList());
}
