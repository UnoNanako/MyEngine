#include <Windows.h>
#pragma once

//WindowsAPI
class WinApiManager
{
public: //メンバ関数
	//定数　クライアント領域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;
	//初期化
	void Initialie();
	//更新
	void Update();
	//getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return wc.hInstance; }
private:
	//ウィンドウハンドル
	HWND hwnd = nullptr;
	WNDCLASS wc{};
};

