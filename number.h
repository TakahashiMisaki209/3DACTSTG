//======================================================
// 
// ナンバーの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//*****************************************************************************
// ナンバークラス
//*****************************************************************************
class CNumber
{
public:

	// コンストラクタ
	CNumber();
	// デストラクタ
	~CNumber();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	// 静的メンバ関数
	static CNumber* Create(D3DXVECTOR3 pos);

private:

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	D3DXVECTOR3 pos;						// 位置
	float fWidth;							// 横幅
	float fHeight;							// 縦幅
	int m_nNumber;							// ナンバーを持つ変数
	int m_nColume;							// 桁数
	int m_nIdxTexture;						// テクスチャの番号
};

#endif
