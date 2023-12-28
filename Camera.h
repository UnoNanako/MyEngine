#pragma once
#include "MyMath.h"
#include "Transform.h"

class DirectXCommon;

class Camera
{
public:
	void Initialize();
	void Update();
	void SetTransform(Transform transform) { this->transform = transform; }
	Matrix4x4 GetViewMatrix() { return viewMatrix; }
	Matrix4x4 GetProjectionMatrix() { return projectionMatrix; }
private:
	Transform transform;
	Matrix4x4 matrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
};

