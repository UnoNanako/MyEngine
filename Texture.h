#pragma once
#include "externals/DirectXTex/DirectXTex.h"
#include <string>
#include <d3d12.h>

class DirectXCommon;

class Texture
{
public:
	void Create(DirectXCommon* dxCommon,const std::string& filePath);
	void Bind(ID3D12GraphicsCommandList* commandList);
	uint32_t GetWidth() { return width; }
	uint32_t GetHeight() { return height; }
private:
	ID3D12Resource* textureResource;
	uint32_t width;
	uint32_t height;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;
	static uint32_t index;
	DirectX::ScratchImage LoadTexture(const std::string& filePath);
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
};
