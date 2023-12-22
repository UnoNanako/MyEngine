#include "Game.h"
#include "WinApiManager.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "SphereModel.h"
#include "Texture.h"
#include "ImGuiManager.h"
#include "Transform.h"
#include "VertexData.h"

void Game::Initialize()
{
	//ポインタ
	winApiManager = nullptr;
	//WindowsAPIの初期化
	winApiManager = new WinApiManager();
	winApiManager->Initialize();

	//入力の初期化
	input = nullptr;
	input = new Input();
	input->Initialize(winApiManager);
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApiManager);

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();
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

	//Imgui
	imgui = new ImGuiManager;
	imgui->Initialize(winApiManager, dxCommon);
}

void Game::Finalize()
{
	//解放処理
	//WindowsAPIの終了処理
	winApiManager->Finalize();
	//ImGuiの終了処理
	imgui->Finalize();
	delete input;
	delete winApiManager;
	delete dxCommon;
	delete spriteCommon;
	delete sprite;
	delete model;
	delete texture;
	delete sphere;
	delete imgui;
}

void Game::Update()
{
	Transform spriteTransform = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	sprite->SetTransform(spriteTransform);

	imgui->Begin();
	//入力の更新
	input->Update();
	//キーが押されているときの処理例
			//数字の0キーが押されていたら
	if (input->PushKey(DIK_0)) {
		OutputDebugStringA("Hit 0\n");
	}

	sprite->Update();
	model->Update();
	sphere->Update();
}

void Game::Draw()
{
	dxCommon->PreDraw();
	imgui->End();
	sprite->Draw(dxCommon->GetCommandList());
	sphere->Draw(dxCommon->GetCommandList());
	model->Draw(dxCommon->GetCommandList());
	//実際のcommandListのImGuiの描画コマンドを積む
	imgui->Draw(dxCommon);
	dxCommon->PostDraw();
}
