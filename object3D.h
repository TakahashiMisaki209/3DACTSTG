//======================================================
// 
// オブジェクト3Dの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// オブジェクト3Dクラス
//*****************************************************************************
class CObject3D :public CObject
{
public:

	// コンストラクタ
	CObject3D(int nPriority = 3);
	// デストラクタ
	~CObject3D();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報の取得

private:

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 頂点座標
	D3DXVECTOR3 m_rot;					// 向き
	float m_fWidth;						// ポリゴンの横幅
	float m_fHeight;					// ポリゴンの縦幅
	bool m_bWireFrame;					// ワイヤーフレームをオンにするかどうか
	int m_nIdxTexture;					// テクスチャの番号
};
#endif