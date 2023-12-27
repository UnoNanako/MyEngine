#pragma once
#include "MyMath.h"
#include <string>

using namespace std;

//マテリアル
struct Material {
	Vector4 color;
	int32_t enableLighting;
};

//マテリアルデータ
struct MaterialData {
	std::string textureFilePath;
};