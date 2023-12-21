#include "ImGuiManager.h"
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
#include "WinApiManager.h"
#include "DirectXCommon.h"
#include <Windows.h>
#include <format>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <fstream>
#include <sstream>

void ImGuiManager::Initialize(WinApiManager* winApp, DirectXCommon* dxCommon)
{
	//ImGuiのコンテキストを生成
	ImGui::CreateContext();
	//ImGuiのスタイルを設定
	ImGui::StyleColorsDark();
	//Win32用初期化
	ImGui_ImplWin32_Init(winApp->GetHwnd());
	auto srvHeap = dxCommon->GetSrvDescriptorHeap();
	//DirectX12用初期化
	ImGui_ImplDX12_Init(
		dxCommon->GetDevice(),
		static_cast<int>(dxCommon->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap,
		srvHeap->GetCPUDescriptorHandleForHeapStart(),
		srvHeap->GetGPUDescriptorHandleForHeapStart()
	);
	//フォント追加
	ImGuiIO& io = ImGui::GetIO();
	//標準フォントを追加する
	io.Fonts->AddFontDefault();
}

void ImGuiManager::Finalize()
{
	//後始末
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::Begin()
{
}

void ImGuiManager::End()
{
}

void ImGuiManager::Draw()
{
}
