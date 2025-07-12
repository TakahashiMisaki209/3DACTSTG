//======================================================
// 
// スコアの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "number.h"
#include "object.h"

// 最大桁数
#define MAX_COLUMES (8)

//*****************************************************************************
// スコアクラス
//*****************************************************************************
class CScore :public CObject
{
public:
	// コンストラクタ
	CScore(int nPriority = 7);
	// デストラクタ
	~CScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CScore* Create(void);
	static void AddScore(int nScore);

private:

	// メンバ変数
	D3DXVECTOR3 m_pos;						// 位置

	// 静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャのポインタ
	static CNumber* m_apNumer[MAX_COLUMES];
	static int m_nScore;					// スコア
};

#endif
