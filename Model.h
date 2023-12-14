#pragma once
#include <vector>
#include "VertexData.h"
#include "Material.h"
#include <string>
using namespace std;

//モデルデータ
struct ModelData {
	vector<VertexData> vertices;
	MaterialData material;
};

class Model
{
public:
	//マテリアルデータを読む関数
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
	//OBJファイルを読む関数
	ModelData LoadObjFile(const string& directoryPath, const string& filename);
};