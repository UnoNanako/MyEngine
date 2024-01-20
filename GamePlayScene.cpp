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

	terrainTexture = new Texture();
	terrainTexture->Create(dxCommon, "resources/grass.png");

	floorModel = new Model;
	floorModel->Create(dxCommon, "resources/floor.obj");

	terrainModel = new Model;
	terrainModel->Create(dxCommon, "resources/terrain.obj");

	//カメラの初期化
	camera = new Camera;
	camera->Initialize(dxCommon);

	//directionalLightの初期化
	mDirectionalLight = new LightList;
	mDirectionalLight->Create(dxCommon);

	//pointLightの初期化
	mPointLight = new LightList;
	mPointLight->Create(dxCommon);

	//spotLightの初期化
	mSpotLight = new LightList;
	mSpotLight->Create(dxCommon);
}

void GamePlayScene::Finalize()
{
	delete sprite;
	delete model;
	delete texture;
	delete terrainTexture;
	delete sphere;
	delete floorModel;
	delete terrainModel;
	delete camera;
	delete mDirectionalLight;
	delete mPointLight;
	delete mSpotLight;
}

void GamePlayScene::Update()
{
	Transform spriteTransform = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	sprite->SetTransform(spriteTransform);
	sprite->Update();
	sphere->Update();
	floorModel->SetScale({2.0f, 2.0f, 2.0f});
	camera->Update();
	mPointLight->Update();
	mSpotLight->Update();
}

void GamePlayScene::Draw(DirectXCommon* dxCommon)
{
	//sprite->Draw(dxCommon->GetCommandList());
	camera->Bind(dxCommon->GetCommandList());
	mDirectionalLight->Bind(dxCommon->GetCommandList());
	mPointLight->Bind(dxCommon->GetCommandList());
	mSpotLight->Bind(dxCommon->GetCommandList());
	texture->Bind(dxCommon->GetCommandList());
	//terrainTexture->Bind(dxCommon->GetCommandList());
	sphere->Draw(dxCommon->GetCommandList(),camera);
	terrainModel->Draw(dxCommon->GetCommandList(), camera);
	//model->Draw(dxCommon->GetCommandList());
	//floorModel->Draw(dxCommon->GetCommandList(),camera);
}
