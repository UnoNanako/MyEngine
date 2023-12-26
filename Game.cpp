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
#include "GamePlayScene.h"

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

	//Imgui
	imgui = new ImGuiManager;
	imgui->Initialize(winApiManager, dxCommon);

	//ゲームプレイシーンの生成
	scene_ = new GamePlayScene();
	//ゲームプレイシーンの初期化
	scene_->Initialize(dxCommon);
}

void Game::Finalize()
{
	//解放処理
	//WindowsAPIの終了処理
	winApiManager->Finalize();
	//ImGuiの終了処理
	imgui->Finalize();
	//ゲームプレイシーンの終了処理
	scene_->Finalize();
	//シーンの解放
	delete scene_;
	delete input;
	delete winApiManager;
	delete dxCommon;
	delete spriteCommon;
	delete imgui;
}

void Game::Update()
{
	imgui->Begin();
	//入力の更新
	input->Update();
	//キーが押されているときの処理例
			//数字の0キーが押されていたら
	if (input->PushKey(DIK_0)) {
		OutputDebugStringA("Hit 0\n");
	}
	//シーンの更新処理
	scene_->Update();
}

void Game::Draw()
{
	dxCommon->PreDraw(); //描画前コマンド
	imgui->End();
	//シーン描画
	scene_->Draw(dxCommon);
	//実際のcommandListのImGuiの描画コマンドを積む
	imgui->Draw(dxCommon);
	dxCommon->PostDraw(); //描画後コマンド
}
