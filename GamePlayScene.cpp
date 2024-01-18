#include "DirectXCommon.h"
#include "GamePlayScene.h"
#include "Model.h"
#include "SphereModel.h"
#include "Sprite.h"
#include "Texture.h"
#include "Transform.h"
#include "VertexData.h"
#include "Camera.h"
#include "LightList.h"

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
	sphere->SetTranslate({ 0.0f,0.0f,10.0f });

	texture = new Texture();
	texture->Create(dxCommon, "resources/UVChecker3.png");

	floorModel = new Model;
	floorModel->Create(dxCommon, "resources/floor.obj");

	//カメラの初期化
	camera = new Camera;
	camera->Initialize();

	//directionalLightの初期化
	mDirectionalLight = new LightList;
	mDirectionalLight->Create(dxCommon);
}

void GamePlayScene::Finalize()
{
	delete sprite;
	delete model;
	delete texture;
	delete sphere;
	delete floorModel;
	delete camera;
	delete mDirectionalLight;
}

void GamePlayScene::Update()
{
	Transform spriteTransform = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	sprite->SetTransform(spriteTransform);
	sprite->Update();
	model->Update();
	sphere->Update();
	floorModel->Update();
	floorModel->SetScale({2.0f, 2.0f, 2.0f});
	camera->Update();
}

void GamePlayScene::Draw(DirectXCommon* dxCommon)
{
	//sprite->Draw(dxCommon->GetCommandList());
	mDirectionalLight->Bind(dxCommon->GetCommandList());
	texture->Bind(dxCommon->GetCommandList());
	sphere->Draw(dxCommon->GetCommandList());
	//model->Draw(dxCommon->GetCommandList());
	//floorModel->Draw(dxCommon->GetCommandList(),camera);
}
