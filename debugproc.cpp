//======================================================
// 
// デバック表示処理
// Author:Takahashi Misaki
// 
//======================================================

#include "debugproc.h"
#include "manager.h"

// 静的メンバ変数宣言
LPD3DXFONT CDebugproc::m_pFont = NULL;
char CDebugproc::m_aStr[1024] = {};
int CDebugproc::m_nIdx = 0;

//********************************************
// コンストラクタ
//********************************************
CDebugproc::CDebugproc()
{
	m_pFont = NULL;

	for (int nCount = 0; nCount < 1024; nCount++)
	{
		m_aStr[nCount] = NULL;
	}
}

//********************************************
// デストラクタ
//********************************************
CDebugproc::~CDebugproc()
{
}

//********************************************
// 初期化処理
//********************************************
void CDebugproc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(pDevice,			// デバイス
		18,							// フォントの高さ
		0,							// フォントの横幅
		0,							// フォントの太さ
		0,							// 下線
		FALSE,						// 斜体
		SHIFTJIS_CHARSET,			// 文字セット
		OUT_DEFAULT_PRECIS,			// 出力制度
		DEFAULT_QUALITY,			// 文字品質
		DEFAULT_PITCH | FF_SWISS,	// ピッチとファミリ
		"Terminal",					// フォント名
		&m_pFont);					// Fontポインタ

}

//********************************************
// 終了処理
//********************************************
void CDebugproc::Uninit(void)
{
	m_pFont = NULL;

	for (int nCount = 0; nCount < 1024; nCount++)
	{
		m_aStr[nCount] = NULL;
	}

}

//********************************************
// プリント処理
//********************************************
void CDebugproc::Print(const char* fmt, ...)
{
	// 引数を格納するリスト
	va_list arg;

	// fmtより後ろの全ての引数をリストに格納する
	va_start(arg, fmt);

	// 現在のバッファの先頭に保管
	m_nIdx += vsnprintf(&m_aStr[m_nIdx], *fmt, fmt, arg);

	// リストの中身をクリアする
	va_end(arg);
}

//********************************************
// 描画処理
//********************************************
void CDebugproc::Draw(void)
{
	// フォントの座標
	RECT rc = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// フォントの描画
	m_pFont->DrawText(NULL,					// NULL
		&m_aStr[0],							// 描画するテキスト
		-1,									// テキストの長さ
		&rc,								// 表示範囲
		DT_LEFT,							// 左寄り
		D3DCOLOR_ARGB(255, 255, 0, 0));	// 色

	for (int nCount = 0; nCount < 1024; nCount++)
	{
		m_aStr[nCount] = NULL;
	}

	// インデックスのクリア
	m_nIdx = 0;

}