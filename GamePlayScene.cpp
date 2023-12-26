#include "DirectXCommon.h"
#include "GamePlayScene.h"
#include "Model.h"
#include "SphereModel.h"
#include "Sprite.h"
#include "Texture.h"
#include "Transform.h"
#include "VertexData.h"

void GamePlayScene::Initialize(DirectXCommon* dxCommon)
{
	//スプライトの初期化
	sprite = new Sprite();
	sprite->Create(dxCommon, "resources/UVChecker3.png");

	//モデルの初期化
	model = new Model;
	// モデル読み込み
	model->Create(dxCommon, "resources/usagi.obj");

	//球体の初期化
	sphere = new SphereModel;
	//球体の読み込み
	sphere->Create(dxCommon);

	texture = new Texture();
	texture->Create(dxCommon, "resources/UVChecker3.png");
}

void GamePlayScene::Finalize()
{
	delete sprite;
	delete model;
	delete texture;
	delete sphere;
}

void GamePlayScene::Update()
{
	Transform spriteTransform = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	sprite->SetTransform(spriteTransform);
	sprite->Update();
	model->Update();
	sphere->Update();
}

void GamePlayScene::Draw(DirectXCommon* dxCommon)
{
	sprite->Draw(dxCommon->GetCommandList());
	sphere->Draw(dxCommon->GetCommandList());
	model->Draw(dxCommon->GetCommandList());
}
