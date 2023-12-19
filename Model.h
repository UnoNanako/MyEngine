#pragma once
#include <d3d12.h>
#include <string>
#include "Transform.h"
#include "Material.h"
#include <vector>
#include <Windows.h>
#include <wrl.h>

using namespace std;

class DirectXCommon;
class Texture;
struct Material;
struct TransformationMatrix;
struct VertexData;

//モデルデータ
struct ModelData {
	vector<VertexData> vertices;
	MaterialData material;
};

class Model
{
public:
	void Create(DirectXCommon* dxCommon,const std::string& filePath);
	void Update();
	void Draw(ID3D12GraphicsCommandList* commandList);
	//マテリアルデータを読む関数
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
	//OBJファイルを読む関数
	void LoadObjFile(const std::string& filePath);
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;
	Material* materialData;
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationMatrixResource;
	TransformationMatrix* transformationMatrixData;
	Transform transform;
	ModelData modelData;
};