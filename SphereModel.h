#pragma once
#include <numbers>
#include <d3d12.h>
#include "Transform.h"

class DirectXCommon;
struct VertexData;
struct Material;

class SphereModel
{
public:
	void Create(DirectXCommon* dxCommon);
	void Update();
	void Draw(ID3D12GraphicsCommandList *commandList);

	const uint32_t kSubdivision = 16; //分割数
	const uint32_t kVertexCount = kSubdivision * kSubdivision * 6;//球体頂点数
	const float kPi = std::numbers::pi_v<float>;
	const float kLonEvery = (2 * kPi) / float(kSubdivision); //経度分割1つ分の角度
	const float kLatEvery = kPi / float(kSubdivision); //緯度分割1つ分の角度
	Transform transform;
	Transform cameraTransform;
	ID3D12Resource* vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	VertexData* vertexData;
	ID3D12Resource* materialResource;
	Material* materialData;
	TransformationMatrix* wvpData;
	ID3D12Resource* wvpResource;
	
};

