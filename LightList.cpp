#include "LightList.h"
#include "DirectXCommon.h"
#include "MyMath.h"
#include "Transform.h"
#include "VertexData.h"

void LightList::Create(DirectXCommon* dxCommon)
{
	mDirectionalLightResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(DirectionalLightForGPU));
	mDirectionalLightData = nullptr;
	mDirectionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(mDirectionalLightData));
}
