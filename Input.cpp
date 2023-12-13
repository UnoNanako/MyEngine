#include "Input.h"
#include <cassert>
#include "WinApiManager.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize(WinApiManager* winApiManager)
{
	//借りてきたWinApiManagerのインスタンスを記録
	this->winApiManager = winApiManager;
	HRESULT hr;
	//DirectInputオブジェクトの生成
	IDirectInput8* directInput = nullptr;
	hr = DirectInput8Create(
		winApiManager->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(hr));
	hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(hr));
	//入力データ形式のセット
	hr = keyboard->SetDataFormat(&c_dfDIKeyboard); //標準形式
	assert(SUCCEEDED(hr));
	//排他制御レベルのセット

	hr = keyboard->SetCooperativeLevel(
		winApiManager->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(hr));
}

void Input::Update()
{
	//キーボード情報の取得開始
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(keys), keys);
}

bool Input::PushKey(BYTE keyNumber) {
	//0で無ければ押している
	if (keys[keyNumber]) {
		return true;
	}
	//押していない
	return false;
}

//キーがトリガーか関数
bool Input::TriggerKey(BYTE keyNumber) {
	//前回が0で今回が0出なければトリガー
	if (!preKeys[keyNumber] && keys[keyNumber]) {
		return true;
	}
	//トリガーではない
	return false;
}
