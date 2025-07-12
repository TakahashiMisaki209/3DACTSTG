//======================================================
// 
// ビルボードの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "object.h"

#define MAX_TEXTURE_W (100.0f)	// 横幅
#define MAX_TEXTURE_H (100.0f)	// 縦幅

//******************************************************
// ビルボードクラス
//******************************************************
class CObjectBillboard :public CObject
{
public:
	// コンストラクタ
	CObjectBillboard(int nPriority = 2);
	// デストラクタ
	~CObjectBillboard();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CObjectBillboard* Create(D3DXVECTOR3 pos);

private:
	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 頂点座標
	D3DXVECTOR3 m_rot;					// 向き
	int m_nIdxTexture;					// テクスチャの番号
};

#endif