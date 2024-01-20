#include "LightList.h"
#include "DirectXCommon.h"
#include "MyMath.h"
#include "Transform.h"
#include "VertexData.h"
#include "externals/imgui/imgui.h"

void LightList::Create(DirectXCommon* dxCommon)
{
	assert(dxCommon);
	mDirectionalLightResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(DirectionalLightForGPU));
	mDirectionalLightData = nullptr;
	mDirectionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&mDirectionalLightData));
	mDirectionalLightData->color = { 0.0f,0.0f,0.0f,1.0f };
	mDirectionalLightData->direction = { 0.0f,-1.0f,0.0f };
	mDirectionalLightData->intensity = 1.0f;

	mPointLightResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(PointLightForGPU));
	mPointLightData = nullptr;
	mPointLightResource->Map(0, nullptr, reinterpret_cast<void**>(&mPointLightData));
	mPointLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	mPointLightData->position = { 0.0f,0.0f,0.0f };
	mPointLightData->intensity = 1.0f;
	mPointLightData->radius = 10.0f;
	mPointLightData->decay = 1.0f;
}

void LightList::Update()
{
	ImGui::Begin("Debug");
	ImGui::DragFloat3("PointLight Position", &mPointLightData->position.x, 0.01f,0.0f,10.0f);
	ImGui::DragFloat("PointLight Radius", &mPointLightData->radius, 0.01f);
	ImGui::DragFloat("PointLight Decay", &mPointLightData->decay, 0.01f, 1.0f, 10.0f);
	ImGui::End();
}

void LightList::Bind(ID3D12GraphicsCommandList* commandList)
{
	commandList->SetGraphicsRootConstantBufferView(3,mDirectionalLightResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(5, mPointLightResource->GetGPUVirtualAddress());
}
