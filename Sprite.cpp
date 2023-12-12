#include "Sprite.h"

void Sprite::Initialize()
{
	//Sprite用のマテリアルリソースを作る
	ID3D12Resource* materialResourceSprite = CreateBufferResource(dxCommon->GetDevice(), sizeof(Material));
	//データを書き込む
	Material* materialDataSprite = nullptr;
	//書き込むためのアドレスを取得
	materialResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSprite));
	//SpriteはLightingしないのでfalseを設定する
	materialDataSprite->enableLighting = false;

	//Sprite用のTransformMatrix用のリソースを作る。Matrix4x4。1つ分のサイズを用意する
	ID3D12Resource* transformationMatrixResourceSprite = CreateBufferResource(dxCommon->GetDevice(), sizeof(TransformationMatrix));
	//データを書き込む
	TransformationMatrix* transformationMatrixDataSprite = nullptr;
	//書き込むためのアドレスを取得
	transformationMatrixResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSprite));
	//単位行列を書き込んでおく
	transformationMatrixDataSprite->WVP = MakeIdentity4x4();
	transformationMatrixDataSprite->World = MakeIdentity4x4();
	//CPUで動かす用のTransformｗｐ作る
	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
}
