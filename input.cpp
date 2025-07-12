//======================================================
// 
// 入力処理
// Author:Takahashi Misaki
// 
//======================================================

#include "input.h"
#include "manager.h"

// 静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//********************************************
// コンストラクタ
//********************************************
CInput::CInput()
{
	m_pInput = NULL;
	m_pDevice = NULL;
}

//********************************************
// デストラクタ
//********************************************
CInput::~CInput()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// Directinputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

	}

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CInput::Uninit()
{
	// 入力デバイス（キーボード）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// Directinputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================
// キーボードの処理
//=============================================

//********************************************
// コンストラクタ
//********************************************
CInputKeyboard::CInputKeyboard()
{
	for (int nCount = 0; nCount < MAX_NUM_KEY; nCount++)
	{
		m_aKeyState[nCount] = NULL;
		m_aOldState[nCount] = NULL;
	}
}

//********************************************
// デストラクタ
//********************************************
CInputKeyboard::~CInputKeyboard()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化処理
	CInput::Init(hInstance, hWnd);

	// 入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CInputKeyboard::Uninit()
{
	// 入力処理の終了処理
	CInput::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_NUM_KEY];
	int nCntKey;

	for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];//ひとつ前のキーボードプレス情報を保存
	}

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// キーボードのアクセス権を獲得
		m_pDevice->Acquire();
	}

}

//********************************************
// キープレス情報を取得
//********************************************
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//********************************************
// キーボードのトリガー情報を取得
//********************************************
bool CInputKeyboard::GetTrigger(int nKey)
{
	bool Trigger = false;

	if (m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;
}
//********************************************
// キーボードのリリース情報を取得
//********************************************
bool CInputKeyboard::GetRelease(int nKey)
{
	bool Trigger = false;

	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;

}
//********************************************
// キーボードのリピート情報を取得
//********************************************
bool CInputKeyboard::GetRepeat(int nKey)
{
	bool Trigger = false;

	if (m_aOldState[nKey] & 0x80 && (m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;
}

////=============================================
//// ジョイパッドの処理
////=============================================
//
////********************************************
//// コンストラクタ
////********************************************
//CInputKeyboard::CInputKeyboard()
//{
//	for (int nCount = 0; nCount < MAX_NUM_KEY; nCount++)
//	{
//		m_aKeyState[nCount] = NULL;
//		m_aOldState[nCount] = NULL;
//	}
//}
//
////********************************************
//// デストラクタ
////********************************************
//CInputKeyboard::~CInputKeyboard()
//{
//
//}
//
////********************************************
//// 初期化処理
////********************************************
//HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
//{
//	// 入力処理の初期化処理
//	CInput::Init(hInstance, hWnd);
//
//	// 入力デバイス（キーボード）の生成
//	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
//	{
//		return E_FAIL;
//	}
//
//	// データフォーマットを設定
//	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
//	{
//		return E_FAIL;
//	}
//
//	// 協調モードを設定
//	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
//		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
//	{
//		return E_FAIL;
//	}
//
//	// ジョイパッドのアクセス権を獲得
//	m_pDevice->Acquire();
//
//	return S_OK;
//}
//
////********************************************
//// 終了処理
////********************************************
//void CInputKeyboard::Uninit()
//{
//	// 入力処理の終了処理
//	CInput::Uninit();
//}
//
////********************************************
//// 更新処理
////********************************************
//void CInputKeyboard::Update()
//{
//	BYTE aKeyState[MAX_NUM_KEY];
//	int nCntKey;
//
//	for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
//	{
//		m_aOldState[nCntKey] = m_aKeyState[nCntKey];//ひとつ前のキーボードプレス情報を保存
//	}
//
//	// 入力デバイスからデータを取得
//	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
//	{
//		for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
//		{
//			m_aKeyState[nCntKey] = aKeyState[nCntKey];
//		}
//	}
//	else
//	{
//		// ジョイパッドのアクセス権を獲得
//		m_pDevice->Acquire();
//	}
//
//}
//
////********************************************
//// ジョイパッドのプレス情報を取得
////********************************************
//bool CInputKeyboard::GetPress(int nKey)
//{
//	return (m_aKeyState[nKey] & 0x80) ? true : false;
//}
////********************************************
//// ジョイパッドのトリガー情報を取得
////********************************************
//bool CInputKeyboard::GetTrigger(int nKey)
//{
//	bool Trigger = false;
//
//	if (m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
//	{
//		Trigger = true;
//	}
//
//	return Trigger;
//}
////********************************************
//// ジョイパッドのリリース情報を取得
////********************************************
//bool CInputKeyboard::GetRelease(int nKey)
//{
//	bool Trigger = false;
//
//	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
//	{
//		Trigger = true;
//	}
//
//	return Trigger;
//
//}
////********************************************
//// ジョイパッドのリピート情報を取得
////********************************************
//bool CInputKeyboard::GetRepeat(int nKey)
//{
//	bool Trigger = false;
//
//	if (m_aOldState[nKey] & 0x80 && (m_aKeyState[nKey] & 0x80))
//	{
//		Trigger = true;
//	}
//
//	return Trigger;
//
//}

//=============================================
// マウスの処理
//=============================================

//********************************************
// コンストラクタ
//********************************************
CInputMouse::CInputMouse()
{
	m_bCursor = true;		// 使用している状態にする
}

//********************************************
// デストラクタ
//********************************************
CInputMouse::~CInputMouse()
{

}

//********************************************
// 初期化処理
//********************************************
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化処理
	CInput::Init(hInstance, hWnd);

	// 入力デバイス（マウス）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードのアクセス権を獲得
	m_pDevice->Acquire();

	m_hWnd = hWnd;

	return S_OK;
}

//********************************************
// 終了処理
//********************************************
void CInputMouse::Uninit()
{
	// 入力処理の終了処理
	CInput::Uninit();
}

//********************************************
// 更新処理
//********************************************
void CInputMouse::Update()
{
	// 古いマウスの情報を更新
	m_mouseOld = m_mouse;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouse)))
	{// 入力デバイスからデータを取得

		for (int nCntButn = 0; nCntButn < MOUSU_MAX; nCntButn++)
		{// マウスのボタン分回す
			m_Trigger.rgbButtons[nCntButn] = m_mouse.rgbButtons[nCntButn] & ~m_mouseOld.rgbButtons[nCntButn];	// トリガーの判定
			m_Release.rgbButtons[nCntButn] = m_mouseOld.rgbButtons[nCntButn] & ~m_mouse.rgbButtons[nCntButn];	// リリースの判定
		}
	}
	else
	{
		m_pDevice->Acquire();	// マウスのアクセス権を獲得
	}

	// カーソルの位置情報を保存する変数
	POINT cp;	

	// マウス座標を取得する
	GetCursorPos(&cp);

	if (m_bCursor == true)
	{// 使用している状態なら
		// スクリーン座標をクライアント座標に変換する
		if (ScreenToClient(m_hWnd, &cp))
		{
			// デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			// DirectXのサイズを取得する
			float width = 0.0f;
			float height = 0.0f;
			IDirect3DSurface9* pBackBuffer = NULL;

			if (SUCCEEDED(pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer)))
			{
				// バックバッファの取得
				D3DSURFACE_DESC desc;
				pBackBuffer->GetDesc(&desc);
				width = (float)desc.Width;
				height = (float)desc.Height;

				// 取得したら解放
				pBackBuffer->Release(); 
			}
			else
			{
				width = (float)SCREEN_WIDTH;
				height = (float)SCREEN_HEIGHT;
			}

			// クライアント領域のサイズを取得
			RECT clientRect;
			GetClientRect(m_hWnd, &clientRect);

			// クライアント座標をDirectXの座標にスケーリング
			float scaleX = width / (clientRect.right - clientRect.left);
			float scaleY = height / (clientRect.bottom - clientRect.top);

			int fixedX = static_cast<int>(cp.x * scaleX);
			int fixedY = static_cast<int>(cp.y * scaleY);

			// 座標を範囲内に固定
			fixedX = max(0, min((int)width, fixedX));
			fixedY = max(0, min((int)height, fixedY));

			cp.x = fixedX;
			cp.y = fixedY;

			m_mouse.lX = cp.x;
			m_mouse.lY = cp.y;

		}

		// 移動量を計算して代入
		m_move.lX = m_mouse.lX - m_mouseOld.lX;
		m_move.lY = m_mouse.lY - m_mouseOld.lY;
	}
	else if (m_bCursor == false)
	{// 使用していない状態の時
		// スクリーン座標をクライアント座標に変換する
		if (ScreenToClient(m_hWnd, &cp))
		{
			RECT csize = {};		// ウィンドウのサイズ保存用

			// クライアントのサイズ取得
			GetClientRect(m_hWnd, &csize);

			// カーソルの移動量を計算する
			m_move.lX = cp.x - (LONG)((float)csize.right * 0.5f);
			m_move.lY = cp.y - (LONG)((float)csize.bottom * 0.5f);

			// カーソル座標を画面中央に設定
			cp.x = (LONG)((float)csize.right * 0.5f);
			cp.y = (LONG)((float)csize.bottom * 0.5f);

			if (ClientToScreen(m_hWnd, &cp))
			{// スクリーン座標に戻す
				// カーソル位置を設定
				SetCursorPos(cp.x, cp.y);
			}
		}
	}
}
