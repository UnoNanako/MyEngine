#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <array>
#include "WinApiManager.h"

//DirectX基盤
class DirectXCommon
{
public:
	//初期化
	void Initialize(WinApiManager* winApiManager);
	//deviceゲッター
	ID3D12Device* GetDevice() { return device.Get(); }
private:
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	//WindowsAPI
	WinApiManager* winApiManager = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap;
	//スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResource;

	ID3D12CommandQueue* commandQueue;
	ID3D12Resource* depthBuffer;
	IDXGISwapChain4* swapChain;
	const uint32_t descriptorSizeSRV;
	const uint32_t descriptorSizeRTV;
	const uint32_t descriptorSizeDSV;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//デバイスの初期化
	void CreateDevice();
	//コマンド関連の初期化
	void InitializeCommand();
	//スワップチェーンの生成
	void CreateSwapChain();
	//深度バッファの生成
	void ClearDepthBuffer();
	//各種デスクリプタヒープの生成
	void CreateEachDescriptorHeap();
	//ディスクリプタヒープを生成する
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	//レンダーターゲットビューの初期化
	void InitializeRenderTargetView();
	//指定番号のCPUデスクリプタハンドルを取得する
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	//指定番号のGPUデスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	//SRVの指定番号のCPUデスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	//SRVの指定番号のGPUデスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);
	//深度ステンシルビューの初期化
	void InitializeDepthStencilView();
	//フェンスの生成
	void CreateFence();
	//ビューポート矩形の初期化
	void InitializeViewport();
	//シザリング矩形の初期化
	void InitializeScissor();
	//DXCコンパイラの生成
	void CreateCompiler();
	//ImGuiの初期化
	void InitializeImGui();
};

