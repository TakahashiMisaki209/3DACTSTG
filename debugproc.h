//======================================================
// 
// デバック表示処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

//*****************************************************************************
// デバック表示クラス
//*****************************************************************************
class CDebugproc
{
public:
	// コンストラクタ
	CDebugproc();
	// デストラクタ
	~CDebugproc();

	// メンバ関数
	void Init(void);
	void Uninit(void);
	
	// 静的メンバ関数
	static void Print(const char* fmt, ...);
	static void Draw(void);

private:

	// 静的メンバ変数
	static LPD3DXFONT m_pFont;	// フォントへのポインタ
	static char m_aStr[1024];	// 文字列を格納するバッファ
	static int m_nIdx;			// 現在のバッファの位置

};

#endif _DEBUGPROC_H_