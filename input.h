//======================================================
// 
// 入力処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

// マクロ定義
#define MAX_NUM_KEY (256)

//*****************************************************************************
// インプットクラス
//*****************************************************************************
class CInput
{
public:
	// コンストラクタ
	CInput();
	// デストラクタ
	virtual ~CInput();

	// メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	// 静的メンバ変数
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;

};

//*****************************************************************************
// キーボードクラス
//*****************************************************************************
class CInputKeyboard:public CInput
{
public:
	// コンストラクタ
	CInputKeyboard();
	// デストラクタ
	~CInputKeyboard();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[MAX_NUM_KEY];
	BYTE m_aOldState[MAX_NUM_KEY];

};

//*****************************************************************************
// マウスクラス
//*****************************************************************************
class CInputMouse :public CInput
{
public:

	// マウスのボタンの種類
	typedef enum
	{
		MOUSE_LEFT = 0,
		MOUSU_RIGHT,
		MOUSU_MAX
	}MOUSU;

	// コンストラクタ
	CInputMouse();
	// デストラクタ
	~CInputMouse();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(MOUSU mousubutten) { return (m_mouse.rgbButtons[mousubutten] & 0x80) ? true : false; };
	bool GetTrigger(MOUSU mousubutten){ return (m_Trigger.rgbButtons[mousubutten] & 0x80) ? true : false; };
	bool GetRelease(MOUSU mousubutten){ return (m_Release.rgbButtons[mousubutten] & 0x80) ? true : false; };
	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3((float)m_mouse.lX, (float)m_mouse.lY, (float)m_mouse.lZ); };
	D3DXVECTOR3 GetMove(void) { return D3DXVECTOR3((float)m_move.lX, (float)m_move.lY, (float)m_move.lZ); };

private:
	DIMOUSESTATE m_mouse;		// マウスの情報
	DIMOUSESTATE m_move;		// マウスの移動量情報
	DIMOUSESTATE m_mouseOld;	// 古いマウスの情報
	DIMOUSESTATE m_Trigger;		// マウストリガーの情報
	DIMOUSESTATE m_Release;		// マウスリリースの情報
	bool m_bCursor;				// カーソルを使用するかどうか
	HWND m_hWnd;
};

////*****************************************************************************
//// ジョイパッドクラス
////*****************************************************************************
//class CInputJoypad :public CInput
//{
//public:
//
//	// ボタンの種類
//	typedef enum
//	{
//		JOYKEY_UP = 0,			// 十字キー上
//		JOYKEY_DOWN,			// 十字キー下
//		JOYKEY_LEFT,			// 十字キー左
//		JOYKEY_RIGHT,			// 十字キー右
//		JOYKEY_START,			// スタートボタン
//		JOYKEY_BACK,			// バックボタン
//		JOYKEY_LSTICK_BUTTON,	// Lスティックボタン
//		JOYKEY_RSTICK_BUTTON,	// Rスティックボタン
//		JOYKEY_L1,				// L1ボタン
//		JOYKEY_R1,				// R1ボタン
//		JOYKEY_L2,				// L2トリガー
//		JOYKEY_R2,				// R2トリガー
//		JOYKEY_A,				// Aボタン
//		JOYKEY_B,				// Bボタン
//		JOYKEY_X,				// Xボタン
//		JOYKEY_Y,				// Yボタン
//		JOYKEY_MAX
//	}JOYKEY;
//
//	// コンストラクタ
//	CInputJoypad();
//	// デストラクタ
//	~CInputJoypad();
//
//	// メンバ関数
//	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
//	void Uninit(void);
//	void Update(void);
//	bool GetPress(int nKey);
//	bool GetTrigger(int nKey);
//	bool GetRelease(int nKey);
//	bool GetRepeat(int nKey);
//
//private:
//	BYTE m_aKeyState[MAX_NUM_KEY];
//	BYTE m_aOldState[MAX_NUM_KEY];
//
//};

#endif 