#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <fstream>
#include <sstream>
#include <random>
#include <numbers>
#include <wrl.h>
#include "externals/DirectXTex/DirectXTex.h"
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
#include "MT3.h"
#include "Input.h"
#include "WinApiManager.h"
#include "DirectXCommon.h"
#include "Logger.h"
#include "StringUtility.h"
#include "Sprite.h"
#include "SpriteCommon.h" 
#include "VertexData.h"
#include "Material.h"
#include "Texture.h"
#include "Model.h"
#include "SphereModel.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

using namespace std;

//Particle構造体
struct Particle {
	Transform transform;
	Vector3 velocity;
	Vector4 color;
	float lifeTime;
	float currentTime;
};

struct ParticleForGPU {
	Matrix4x4 WVP;
	Matrix4x4 World;
	Vector4 color;
};

//平行光源(Directional Light)
struct DirectionalLight {
	Vector4 color; //ライトの色
	Vector3 direction; //ライトの向き
	float intensity; //輝度
};

//Particle生成関数
Particle MakeNewParticle(std::mt19937& randomEngine) {
	//位置と速度を[-1,1]でランダムに初期化
	std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
	std::uniform_real_distribution<float> distColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> distTime(1.0f, 3.0f);
	Particle particle;
	particle.transform.scale = { 1.0f,1.0f,1.0f };
	particle.transform.rotate = { 0.0f,0.0f,0.0f };
	particle.transform.translate = { distribution(randomEngine), distribution(randomEngine), distribution(randomEngine) };
	particle.velocity = { distribution(randomEngine), distribution(randomEngine), distribution(randomEngine) };
	particle.color = { distColor(randomEngine), distColor(randomEngine), distColor(randomEngine), 1.0f };
	particle.lifeTime = distTime(randomEngine);
	particle.currentTime = 0;
	return particle;
}

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	//ポインタ
	WinApiManager* winApiManager = nullptr;
	//WindowsAPIの初期化
	winApiManager = new WinApiManager();
	winApiManager->Initialize();

	//入力の初期化
	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApiManager);
	DirectXCommon* dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApiManager);

	//スプライト共通部分の初期化
	SpriteCommon* spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();
	//スプライトの初期化
	Sprite* sprite = new Sprite();
	sprite->Create(dxCommon, "resources/UVChecker3.png");

	//モデルの初期化
	Model* model = new Model;
	// モデル読み込み
	model->Create(dxCommon, "resources/usagi.obj");
	
	//球体の初期化
	SphereModel* sphere = new SphereModel;
	//球体の読み込み
	sphere->Create(dxCommon);
	
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 0;  // 0から始まる
	descriptorRange[0].NumDescriptors = 1;  // 数は1つ
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV; // SRVを使う
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // Offsetを自動計算

	//RootSignatureを生成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	// RootParameter作成。複数設定できるので配列。今回は結果1つだけなので長さ1の配列
	D3D12_ROOT_PARAMETER rootParameters[4] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;    // CBVを使う
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;   // PixelShaderで使う
	rootParameters[0].Descriptor.ShaderRegister = 0;    // レジスタ番号0とバインド
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; //CBVを使う
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX; //VertexShaderで使う
	rootParameters[1].Descriptor.ShaderRegister = 0; //レジスタ番号0を使う
	//rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangeForInstancing;  // Tableの中身の配列を指定
	//rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInstancing); // Tableで利用する数
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescriptorTableを使う
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRange;  // Tableの中身の配列を指定
	rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange); // Tableで利用する数
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; //CBVを使う
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; //PixelShaderで使う
	rootParameters[3].Descriptor.ShaderRegister = 1; //レジスタ番号1を使う
	descriptionRootSignature.pParameters = rootParameters;  // ルートパラメータ配列へのポインタ
	descriptionRootSignature.NumParameters = _countof(rootParameters);  // 配列の長さ

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイリニアフィルタ
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;   // 0~1の範囲外をリピート
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;   // ありったけのMipmapを使う
	staticSamplers[0].ShaderRegister = 0;   // レジスタ番号0を使う
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

	//シリアライズしてバイナリにする
	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr)) {
		Logger::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	//バイナリを元に生成
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature = nullptr;
	hr = dxCommon->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(hr));

	//InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	// BlendStateの設定
	D3D12_BLEND_DESC blendDesc{};
	// すべての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	//NormalBlendを行うための設定
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;

	// RasiterzerStateの設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	// 裏面（時計回り）を表示しない
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	// Shaderをコンパイルする
	Microsoft::WRL::ComPtr<IDxcBlob> vertexShaderBlob = dxCommon->CompileShader(L"resources/shaders/Object3d.VS.hlsl", L"vs_6_0", dxCommon->GetUtils(), dxCommon->GetCompiler(), dxCommon->GetHandler());
	assert(vertexShaderBlob != nullptr);

	Microsoft::WRL::ComPtr<IDxcBlob> pixelShaderBlob = dxCommon->CompileShader(L"resources/shaders/Object3d.PS.hlsl", L"ps_6_0", dxCommon->GetUtils(), dxCommon->GetCompiler(), dxCommon->GetHandler());
	assert(pixelShaderBlob != nullptr);

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	graphicsPipelineStateDesc.pRootSignature = rootSignature.Get();// RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;// InputLayout
	graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize() };// VertexShader
	graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize() };// PixelShader
	graphicsPipelineStateDesc.BlendState = blendDesc;// BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;// RasterizerState
	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	// 利用するトポロジ（形状）のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	// どのように画面に色を打ち込むかの設定（気にしなくて良い）
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	// Depthの機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込みします
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	//depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO; //Depthの書き込みを行わない
	// 比較関数はLessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	// DepthStencilの設定
	graphicsPipelineStateDesc.DepthStencilState = depthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 実際に生成
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState = nullptr;
	hr = dxCommon->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&graphicsPipelineState));
	assert(SUCCEEDED(hr));

	//// 左下
	//vertexData[0].position = { -0.5f, -0.5f, 0.0f, 1.0f };
	//vertexData[0].texcoord = { 0.0f,1.0f };
	//// 上
	//vertexData[1].position = { 0.0f, 0.5f, 0.0f, 1.0f };
	//vertexData[1].texcoord = { 0.5f,0.0f };
	//// 右下
	//vertexData[2].position = { 0.5f, -0.5f, 0.0f, 1.0f };
	//vertexData[2].texcoord = { 1.0f,1.0f };

	////左下2
	//vertexData[3].position = { -0.5f,-0.5f,0.5f,1.0f };
	//vertexData[3].texcoord = { 0.0f,1.0f };
	////上2
	//vertexData[4].position = { 0.0f,0.0f,0.0f,1.0f };
	//vertexData[4].texcoord = { 0.5f,0.0f };
	////右下2
	//vertexData[5].position = { 0.5f,-0.5f,-0.5f,1.0f };
	//vertexData[5].texcoord = { 1.0f, 1.0f };

	//インデックス
	///ID3D12Resource* indexResourceSprite = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(uint32_t) * 6);
	///D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};
	///indexBufferViewSprite.BufferLocation = indexResourceSprite->GetGPUVirtualAddress();
	///indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
	///indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;
	///uint32_t* indexDataSprite = nullptr;
	///indexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSprite));
	///indexDataSprite[0] = 0; indexDataSprite[1] = 1; indexDataSprite[2] = 2;
	///indexDataSprite[3] = 1; indexDataSprite[4] = 3; indexDataSprite[5] = 2;

	//Instancing用にTransformationMatrixを10コ格納できるResourceを作る
	const uint32_t kNumMaxInstance = 10; //インスタンス数
	//Instancing用のTransformationMatrixリソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> instancingResource =
		dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(ParticleForGPU) * kNumMaxInstance);
	//書き込むためのアドレスを取得
	ParticleForGPU* instancingData = nullptr;
	instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instancingData));
	//単位行列を書き込んでおく
	for (uint32_t index = 0; index < kNumMaxInstance; ++index) {
		instancingData[index].WVP = MakeIdentity4x4();
		instancingData[index].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		//instancingData[index].World = MakeIdentity4x4();
	}

	//tを定義。とりあえず60fps固定してあるが、実時間を計測して可変fpsで動かせるようにしておくとなお良い。
	const float kDeltaTime = 1.0f / 60.0f;

	//DirectionalLight用のResource
	ID3D12Resource* directionalLightResource = dxCommon->CreateBufferResource(dxCommon->GetDevice(), sizeof(DirectionalLight));
	//データを書き込む
	DirectionalLight* directionalLightData = nullptr;
	//書き込むためのアドレスを取得
	directionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));
	//デフォルト値はとりあえず以下のようにしておく
	directionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLightData->direction = { 0.0f,-1.0f,0.0f };
	directionalLightData->intensity = 1.0f;

	Texture *texture = new Texture();
	texture->Create(dxCommon, "resources/UVChecker3.png");
	
	Transform spriteTransform = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	sprite->SetTransform(spriteTransform);

	MSG msg{};
	//--------------------10. GPUの実行を待つ(fenceは実行を待つものではなく、GPUの処理が終わったかを調べるもの)	//ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		//Windoeにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ゲームの処理
			//フレームの先頭でImGuiに、ここからフレームが始まる旨を告げる
			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			//ゲームの更新処理でパラメータを変更したいタイミングでImGuiの処理を行う
			//今回はImGuiのデモ用のUIを表示している
			//開発用UIの処理。実際に開発用のUIを出す場合はここをゲーム固有の処理に置き換える
			ImGui::ShowDemoWindow();

			///--------------------更新処理ここから--------------------

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

			///--------------------更新処理ここまで--------------------

			dxCommon->PreDraw();

			//--------------------5. 描画コマンド--------------------
			//ImGuiを描画する
			//描画用のDescriptorHeapの設定
			ID3D12DescriptorHeap* descriptorHeaps[] = { dxCommon->GetSrvDescriptorHeap() };
			dxCommon->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);
			// RootSignatureを設定。PSOに設定しているけど別途設定が必要
			dxCommon->GetCommandList()->SetGraphicsRootSignature(rootSignature.Get());
			dxCommon->GetCommandList()->SetPipelineState(graphicsPipelineState.Get());   // PSOを設定
			//commandList->IASetVertexBuffers(0, 1, &vertexBufferView);   // VBVを設定
			// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
			//dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//// マテリアルCBufferの場所を設定
			//dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
			////SRVのDescriptorTableの先頭を設定。2はrootParameter[2]である。
			//texture->Bind(dxCommon->GetCommandList());

			////インデックス
			/////dxCommon->GetCommandList()->IASetIndexBuffer(&indexBufferViewSprite);
			//
			////DirectionalLightの場所を設定
			//dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());
			//ImGui::Begin("Window");
			//ImGui::ColorEdit4("Alpha", &color.x);
			//materialData->color = color;
			//ImGui::End();
			//ゲームの処理が終わり描画処理に入る前に、ImGuiの内部コマンドを生成する
			//ImGuiの内部コマンドを生成する
			ImGui::Render();

			sprite->Draw(dxCommon->GetCommandList());
			//sphere->Draw(dxCommon->GetCommandList());
			model->Draw(dxCommon->GetCommandList());

			//インデックス
			///dxCommon->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);

			//実際のcommandListのImGuiの描画コマンドを積む
			ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dxCommon->GetCommandList());

			dxCommon->PostDraw();
		}
	}
	//WindowsAPIの終了処理
	winApiManager->Finalize();
	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");
	//解放処理
	///materialResource->Release();
	///graphicsPipelineState->Release();
	///signatureBlob->Release();
	///if (errorBlob) {
	///	errorBlob->Release();
	///}
	///rootSignature->Release();
	///pixelShaderBlob->Release();
	///vertexShaderBlob->Release();

	//リソースチェック
	Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		///debug->Release();
	}

	//入力解放
	delete input;
	delete winApiManager;
	delete dxCommon;
	delete spriteCommon;
	delete sprite;
	delete model;

	return 0;
}