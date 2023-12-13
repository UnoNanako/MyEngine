#pragma once
#include <d3d12.h>
#include <string>
#include "Transform.h"

class DirectXCommon;
class Texture;
struct Material;
struct TransformationMatrix;

//スプライト
class Sprite
{
public:
	void Create(DirectXCommon* dxCommon, const std::string& filePath);
	void Update();
	void Draw(ID3D12GraphicsCommandList *commandList);
	void SetTransform(Transform transform) { this->transform = transform; }
private:
	Texture* texture;
	ID3D12Resource* vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	ID3D12Resource* materialResource;
	Material* materialData;
	ID3D12Resource* transformationMatrixResource;
	TransformationMatrix* transformationMatrixData;
	Transform transform;
};

