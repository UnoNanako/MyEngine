#pragma once
#include <cstdint>
#include "DirectionalLight.h"
#include "MyMath.h"
#include <d3d12.h>
#include <wrl.h>

class DirectXCommon;

class LightList
{
public:
	void Create(DirectXCommon* dxCommon);
	void Bind(ID3D12GraphicsCommandList* commandList);

private:
	//定数(シェーダー側と合わせる)
	struct DirectionalLightForGPU {
		Vector4 color;
		Vector3 direction;
		float intensity;
	};

	//DirectionalLightインスタンス
	DirectionalLight directionalLight;

	Microsoft::WRL::ComPtr<ID3D12Resource> mDirectionalLightResource;
	DirectionalLightForGPU* mDirectionalLightData;
};

