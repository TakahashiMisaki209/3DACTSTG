//======================================================
// 
// テクスチャの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

// マクロ定義
#define MAX_NUMTEXTUER (20)

//******************************************************
// テクスチャクラス
//******************************************************
class CTexture
{
public:
	// コンストラクタ
	CTexture();
	// デストラクタ
	~CTexture();

	// メンバ関数
	HRESULT Load(void);
	void Unload(void);
	int Register(const char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_apTexture[nIdx]; };

private:
	// メンバ変数
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_NUMTEXTUER];

	// 静的メンバ変数
	static int m_nNumAll;

};

#endif