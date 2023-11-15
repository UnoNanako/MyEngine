#include "WinApiManager.h"
#include <cstdint>

void WinApiManager::Initialie()
{
	WNDCLASS wc{};
	//COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//ウィンドウプロシージャ
	wc.lpfnWndProc = WindowProc;
	//ウィンドウクラス名(なんでもいい)
	wc.lpszClassName = L"CG2WindowClass";
	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//ウィンドウクラスを登録する
	RegisterClass(&wc);
	//ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };
	//クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの生成
	hwnd = CreateWindow(
		wc.lpszClassName, //利用するクラス名
		L"CG2", //タイトルバーの文字(なんでもいい)
		WS_OVERLAPPEDWINDOW, //よく見るウィンドウスタイル
		CW_USEDEFAULT, //表示X座標(Windowsに任せる)
		CW_USEDEFAULT, //表示y座標(WindowsOSに任せる)
		wrc.right - wrc.left, //ウィンドウ横幅
		wrc.bottom - wrc.top, //ウィンドウ縦幅
		nullptr, //親ウィンドウハンドル
		nullptr, //メニューハンドル
		wc.hInstance, //インスタンスハンドル
		nullptr); //オプション
	//ウィンドウを表示する
	ShowWindow(hwnd, SW_SHOW);
}

void WinApiManager::Update()
{
}
