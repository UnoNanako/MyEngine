#include "Camera.h"
#include "WinApiManager.h"

void Camera::Initialize()
{
	transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-10.0f} };
}

void Camera::Update()
{
	const float kPi = std::numbers::pi_v<float>;
	matrix = MakeAffineMatrix(transform.scale,transform.rotate,transform.translate);
	viewMatrix = Inverse(matrix);
	projectionMatrix = MakePerspectiveFovMatrix(110.0f * (kPi / 180.0f), WinApiManager::kClientWidth / float(WinApiManager::kClientHeight), 0.1f, 1000.0f);
}
