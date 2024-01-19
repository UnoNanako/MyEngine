#include "Camera.h"
#include "WinApiManager.h"
#include "DirectXCommon.h"
#include "externals/imgui/imgui.h"

void Camera::Initialize(DirectXCommon* dxCommon)
{
	transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-10.0f} };
	cameraRresource = dxCommon->CreateBufferResource(dxCommon->GetDevice(),sizeof(Vector3));
	cameraRresource->Map(0, nullptr, reinterpret_cast<void**>(&cameraData));
}

void Camera::Update()
{
	ImGui::Begin("Camera");
	ImGui::DragFloat3("position", &transform.translate.x, 0.05f);
	ImGui::End();
	const float kPi = std::numbers::pi_v<float>;
	matrix = MakeAffineMatrix(transform.scale,transform.rotate,transform.translate);
	viewMatrix = Inverse(matrix);
	projectionMatrix = MakePerspectiveFovMatrix(50.0f * (kPi / 180.0f), WinApiManager::kClientWidth / float(WinApiManager::kClientHeight), 0.1f, 1000.0f);
	*cameraData = { transform.translate };
}

void Camera::Bind(ID3D12GraphicsCommandList* commandList)
{
	commandList->SetGraphicsRootConstantBufferView(4, cameraRresource->GetGPUVirtualAddress());
}
