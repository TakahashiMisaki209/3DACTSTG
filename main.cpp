//======================================================
// 
// window表示処理
// Author:Takahashi Misaki
// 
//======================================================

#include "main.h"
#include "manager.h"

// グローバル変数宣言
int g_nCountFPS = 0;

// プロトタイプ宣言 今後これをコピーして使う
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM iParam);

//********************************************
//メイン関数
//********************************************
// コピーして使いまわす
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hinstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// メモリリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//メモリリーク検知

	// マネージャーのポインタ生成
	CManager* pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; // 画面サイズの構造体

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	// マネージャーの生成
	pManager = new CManager;

	// マネージャーの初期化処理
	pManager->Init(hInstance, hWnd, TRUE);

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 現在の時間
	DWORD dwCurentTime;
	// 実行時間
	DWORD dwExeclastTime;

	// 分解能を設定
	timeBeginPeriod(1);
	dwCurentTime = 0;
	dwExeclastTime = timeGetTime();

	DWORD dwFrameCount;		// フレームカウント
	DWORD dwFPSLastTime;	// 最後にFPSを計測した時刻

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windowの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				// メッセージの設定
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理

			dwCurentTime = timeGetTime();

			if ((dwCurentTime - dwFPSLastTime) >= 500)
			{// 0.5秒計測

				// FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurentTime;		// FPSを測定したときの時刻を保存
				dwFrameCount = 0;					// フレームカウントをクリア

			}
			if ((dwCurentTime - dwExeclastTime) >= (1000 / 60))
			{// 60分の1秒経過

				dwExeclastTime = dwCurentTime;

				// マネージャーの更新処理
				pManager->Update();

				// マネージャーの描画処理
				pManager->Draw();

				dwFrameCount++;		// フレームカウントを加算
			}
		}
	}

	// マネージャーの破棄
	if (pManager != NULL)
	{
		// 終了処理
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//********************************************
//ウインドウプロシージャ
//********************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: // ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);  // 既定の処理を返す
}