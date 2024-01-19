#include "LightList.h"
#include "DirectXCommon.h"
#include "MyMath.h"
#include "Transform.h"
#include "VertexData.h"

void LightList::Create(DirectXCommon* dxCommon)
{
	assert(dxCommon);
	mDirectionalLightResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(DirectionalLightForGPU));
	mDirectionalLightData = nullptr;
	mDirectionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&mDirectionalLightData));
	mDirectionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	mDirectionalLightData->direction = { 0.0f,-1.0f,0.0f };
	mDirectionalLightData->intensity = 1.0f;
}

void LightList::Bind(ID3D12GraphicsCommandList* commandList)
{
	commandList->SetGraphicsRootConstantBufferView(3,mDirectionalLightResource->GetGPUVirtualAddress());
}
