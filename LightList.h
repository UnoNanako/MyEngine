#pragma once
#include <cstdint>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "MyMath.h"
#include <d3d12.h>
#include <wrl.h>

class DirectXCommon;

class LightList
{
public:
	void Create(DirectXCommon* dxCommon);
	void Update();
	void Bind(ID3D12GraphicsCommandList* commandList);

private:
	//定数(シェーダー側と合わせる)
	struct DirectionalLightForGPU {
		Vector4 color;
		Vector3 direction;
		float intensity;
	};

	struct PointLightForGPU {
		Vector4 color; //ライトの色
		Vector3 position; //ライトの位置
		float intensity; //輝度
		float radius; //ライトの届く最大距離
		float decay; //減衰率
	};

	//DirectionalLight
	DirectionalLight directionalLight;
	Microsoft::WRL::ComPtr<ID3D12Resource> mDirectionalLightResource;
	DirectionalLightForGPU* mDirectionalLightData;

	//PointLight
	PointLight pointLight;
	Microsoft::WRL::ComPtr<ID3D12Resource> mPointLightResource;
	PointLightForGPU* mPointLightData;
};

